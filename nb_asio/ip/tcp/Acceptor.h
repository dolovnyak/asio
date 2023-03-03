#pragma once

#include "nb_asio/IoContext.h"
#include "Endpoint.h"
#include "Socket.h"

namespace nb_asio::ip::tcp {

class Acceptor {
public:
    enum class Option {
        ReuseAddress
    };

    Acceptor() = delete;

    Acceptor(nb_asio::IoContext& context);

    void SetOption(const Option& option, bool enable);

    void ListenEndpoint(const tcp::Endpoint& endpoint);

    template<class UserFunctor>
    void AsyncAccept(Socket& socket, UserFunctor&& functor) {

    }
};

}