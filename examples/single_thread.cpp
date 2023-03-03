#include "nb_asio.h"

#include <utility>

class Connection : public std::enable_shared_from_this<Connection> {
public:
    Connection(nb_asio::IoContext& io_context) :
            socket(io_context) {}

    void AsyncReadRequest() {
        nb_asio::LOG_INFO("AsyncReadRequest");

        auto read_lambda = [this_weak_ptr = weak_from_this()](const nb_asio::Error& error,
                                                              std::size_t bytes_transferred) {
            if (!error) {
                auto this_ptr = this_weak_ptr.lock();
                if (this_ptr) {
                    nb_asio::LOG_INFO("Read ", bytes_transferred, " bytes");
                    this_ptr->AsyncWriteResponse(this_ptr->buffer);
                }
            }
            else {
                nb_asio::LOG_ERROR("Error on read");
                return;
            }
        };

        socket.AsyncReadSome(buffer, read_lambda);
    }

    void AsyncWriteResponse(const std::string& response) {
        nb_asio::LOG_INFO("AsyncWriteResponse");
        auto write_lambda = [this_weak_ptr = weak_from_this()](const nb_asio::Error& error,
                                                               size_t bytes_transferred) {
            if (!error) {
                auto this_ptr = this_weak_ptr.lock();
                if (this_ptr) {
                    nb_asio::LOG_INFO("Write ", bytes_transferred, " bytes");
                }
            }
            else {
                nb_asio::LOG_ERROR("Error on write");
            }
        };

        socket.AsyncWrite(response, write_lambda);
    }

    nb_asio::ip::tcp::Socket socket;
    std::string buffer;
};

class Listener {
public:
    Listener(nb_asio::IoContext& io_context, std::string host, int port)
            : endpoint(nb_asio::ip::Address::FromString(std::move(host)), port),
              acceptor(io_context) {
        acceptor.SetOption(nb_asio::ip::tcp::Acceptor::Option::ReuseAddress, true);
        acceptor.ListenEndpoint(endpoint);
    }

    void AsyncAccept(std::shared_ptr<Connection> new_connection) {
        auto accept_lambda = [new_connection](const nb_asio::Error& error) {
            if (!error) {
                nb_asio::LOG_INFO("Accept new connection");
                new_connection->AsyncReadRequest();
            }
            else {
                nb_asio::LOG_ERROR("Error on new connection");
            }
        };
        acceptor.AsyncAccept(new_connection->socket, accept_lambda);
    }

    nb_asio::ip::tcp::Endpoint endpoint;
    nb_asio::ip::tcp::Acceptor acceptor;
};

int main() {
    nb_asio::IoContext io_context;

    Listener listener(io_context, "127.0.0.1", 1234);
    listener.AsyncAccept(std::make_shared<Connection>(io_context));

    io_context.Run();
}