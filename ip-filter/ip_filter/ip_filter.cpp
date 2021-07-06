#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <sstream>
#include <stdint.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <ipv4.h>

using Ipv4Container = std::list<Ipv4>;

template <typename T, typename Pred>
auto filter(const T& container, Pred pred)
{
    T out;
    std::copy_if(cbegin(container), cend(container), std::back_inserter(out), pred);
    return out;
}

template<typename T>
T read_ips_list(std::istream& ss)
{
    T ips;
    for(std::string line; std::getline(std::cin, line);)
    {
        std::string ip;
        std::getline(std::stringstream(line), ip, '\t');
        ips.push_back(Ipv4(ip));
    }
    return ips;
}

int main(int argc, char const *argv[])
{
    try
    {
        // TODO: Here code stops when there is no data in stdin
        Ipv4Container ips = read_ips_list<Ipv4Container>(std::cin);

        // Sort and print
        ips.sort(std::greater<Ipv4>());
        for(const auto& ip : ips) std::cout << ip << std::endl;
 
        // Filter by first byte and print
        {
            const Ipv4 mask("255.0.0.0");
            const Ipv4 val("1.0.0.0");
            auto predicate = [&mask, &val](const Ipv4& ip) -> bool { return (ip.ip & mask.ip) == val.ip; };
            for(const auto& ip : filter(ips, predicate)) std::cout << ip << std::endl;
        }

        // Filter by 2nd and 3rd bytes 
        {
            const Ipv4 mask("255.255.0.0");
            const Ipv4 val("46.70.0.0");
            auto predicate = [&mask, &val](const Ipv4& ip) -> bool { return (ip.ip & mask.ip) == val.ip; };
            for(const auto& ip : filter(ips, predicate)) std::cout << ip << std::endl;
        }

        // Filter by byte
        {
            const Ipv4 mask("255.0.0.0");
            const Ipv4 val("46.0.0.0");
            auto predicate = [&mask, &val](const Ipv4& ip) -> bool {
                for(unsigned bytes_shifted = 0; bytes_shifted < 4; ++bytes_shifted)
                {
                    const unsigned bits_shifted = bytes_shifted*8;
                    if((ip.ip & (mask.ip >> (bits_shifted))) == (val.ip >> (bits_shifted)))
                    {
                        return true;
                    }
                }
                return false;
            };
            for(const auto& ip : filter(ips, predicate)) std::cout << ip << std::endl;
        }
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    return 0;
}
