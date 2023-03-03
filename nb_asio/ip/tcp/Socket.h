#pragma once

#include "nb_asio/IoContext.h"

namespace nb_asio::ip::tcp {

class Socket {
public:
    Socket() = delete;

    Socket(nb_asio::IoContext& context);
};

}