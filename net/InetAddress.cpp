#include <arpa/inet.h>
#include <cstring>

#include "Log.h"
#include "InetAddress.h"

namespace net
{
    InetAddress::InetAddress(const std::string &ip, in_port_t port, sa_family_t family)
    {
        std::memset(&_addr, 0, get_sockaddr_size());

        _addr.sin_family = family;
        _addr.sin_port = htons(port);

        if (::inet_pton(AF_INET, ip.c_str(), &_addr.sin_addr) <= 0) {
            LOG_ERROR << "inet_pton 失败";
        }
    }

    std::string InetAddress::toIp() const
    {
        char s[16]={0};
        ::inet_ntop(AF_INET, &_addr.sin_addr, &s[0], static_cast<socklen_t>(sizeof s));
        return std::string(s);
    }

    std::string InetAddress::toIpPort() const
    {
        return std::to_string(ntohs(_addr.sin_port))+":"+std::to_string(toPort());
    }

    in_port_t InetAddress::toPort() const
    {
        return ntohs(_addr.sin_port);
    }

    uint32_t InetAddress::ipNetEndian() const
    {
        return _addr.sin_addr.s_addr;
    }

    InetAddress::InetAddress(const struct sockaddr_in &addr)
            : _addr(addr)
    {

    }

    const sockaddr *InetAddress::get_sockaddr() const
    {
        return reinterpret_cast<const sockaddr *>(&_addr);
    }

    sockaddr *InetAddress::get_sockaddr()
    {
        return reinterpret_cast<sockaddr *>(&_addr);
    }

    sa_family_t InetAddress::get_family() const
    {
        return _addr.sin_family;
    }

    in_port_t InetAddress::get_port() const
    {
        return _addr.sin_port;
    }
}