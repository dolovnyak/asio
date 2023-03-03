#pragma once

namespace nb_asio {

class Error {
public:
    bool Empty() const;

    bool operator! () const;
};

}