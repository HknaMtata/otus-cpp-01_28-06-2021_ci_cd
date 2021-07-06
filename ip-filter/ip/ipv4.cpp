#include "ipv4.h"

#include <arpa/inet.h>
#include <netinet/in.h>

namespace
{

uint32_t Ipv4FromString(const std::string& str)
{
    struct in_addr addr;
    inet_aton(str.c_str(), &addr);
    return ntohl(addr.s_addr);
}

std::string Ipv4ToString(const uint32_t& ip)
{
    struct in_addr addr;
    addr.s_addr = htonl(ip);
    return inet_ntoa(addr);
}

}

Ipv4::Ipv4()
    : ip(0)
{
}

Ipv4::Ipv4(const std::string& ip_str)
{
    ip = Ipv4FromString(ip_str);
}

bool Ipv4::operator>(const Ipv4& other) const
{
    static const Ipv4 mask("255.0.0.0");
    static const unsigned bits_in_byte = 8;
    for(unsigned bytes_shifted = 0; bytes_shifted < 4; ++bytes_shifted)
    {
        const uint32_t mask_shifted = mask.ip >> (bytes_shifted * bits_in_byte);
        uint32_t lhs = ip & mask_shifted; 
        uint32_t rhs = other.ip & mask_shifted; 
        if (lhs == rhs)
            continue;
        if(lhs > rhs)
            return true;
        if(lhs < rhs)
            return false;        
    }
    return false;
}

bool Ipv4::operator<(const Ipv4& other) const
{
    return !((*this) > other);
}

std::ostream& operator<<(std::ostream& os, const Ipv4& ip)
{
    return os << Ipv4ToString(ip.ip);
}