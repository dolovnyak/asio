#pragma once

#include <string>

namespace nb_asio::ip {

class AddressV4 {

};

class Address {
public:
    static Address FromString(const std::string& str);

    static Address FromString(const char* str);

private:
    Address(const AddressV4& ip_v4_address);
};

}