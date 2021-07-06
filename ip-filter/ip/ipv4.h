#pragma once

#include <string>
#include <stdint.h>
#include <iostream>

class Ipv4
{
public:
    Ipv4();
    Ipv4(const std::string& ip_str);

    bool operator>(const Ipv4& other) const;
    bool operator<(const Ipv4& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Ipv4& ip);

    uint32_t ip;
};

std::ostream& operator<<(std::ostream& os, const Ipv4& ip);