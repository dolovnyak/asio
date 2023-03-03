#pragma once

#include "nb_asio/IoContext.h"

namespace nb_asio::ip::tcp {

class Socket {
public:
    Socket() = delete;

    Socket(nb_asio::IoContext& context);

    template<class UserFunctor>
    void AsyncReadSome(std::string& buffer, UserFunctor&& functor) {} /// TODO create normal buffer with fixed size

    template<class UserFunctor>
    void AsyncRead(std::string& buffer, UserFunctor&& functor) {} /// TODO create normal buffer with fixed size

    template<class UserFunctor>
    void AsyncWriteSome(const std::string& buffer, UserFunctor&& functor) {} /// TODO create normal buffer with fixed size

    template<class UserFunctor>
    void AsyncWrite(const std::string& buffer, UserFunctor&& functor) {} /// TODO create normal buffer with fixed size
};

}