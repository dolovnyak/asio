#pragma once

#include "Address.h"

namespace nb_asio::ip::tcp {

class Endpoint {
public:
    Endpoint(const nb_asio::ip::Address& address, int port);
};

}