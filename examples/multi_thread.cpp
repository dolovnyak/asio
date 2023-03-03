#include "nb_asio.h"

class Connection {
public:
    void AsyncReadRequest() {
        LOG_INFO("AsyncReadRequest");
        auto read_lambda = [this_weak_ptr = weak_from_this()](const boost::system::error_code& error_code,
                                                              std::size_t bytes_transferred) {
            auto this_ptr = this_weak_ptr.lock();
            if (this_ptr) {
                this_ptr->HandleReadRequest(error_code, bytes_transferred);
            }
        };
        _socket.async_read_some(boost::asio::buffer(_buffer), read_lambda);
    }

    nb_asio::ip::tcp::Socket socket;
};

int main() {
    nb_asio::IoContext io_context;

    std::string host = "127.0.0.1";
    int port = 1234;

    nb_asio::ip::tcp::Endpoint endpoint(nb_asio::ip::Address::FromString(host), port);
    nb_asio::ip::tcp::Acceptor acceptor(io_context);

    acceptor.SetOption(nb_asio::ip::tcp::Acceptor::Option::ReuseAddress, true);
    acceptor.ListenEndpoint(endpoint);

    nb_asio::ip::tcp::Socket socket(io_context);

    auto accept_lambda = [](const nb_asio::Error& error) {
        /// TODO log
    };
    acceptor.AsyncAccept(socket, accept_lambda);

    io_context.Run();
}