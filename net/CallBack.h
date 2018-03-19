//
// Created by lg on 17-4-20.
//

#pragma once
#include<memory>

namespace net {

    class TcpConnection;

    class Buffer;

    class InetAddress;

    using TCPConnPtr=std::shared_ptr<TcpConnection>;

    using NewConnCallback = std::function<void(int, const InetAddress &)>;

    using MessageCallback = std::function<void(const TCPConnPtr &, Buffer *)>;


    using ConnectingCallback =std::function<void(const TCPConnPtr &)>;
    using CloseCallback =std::function<void(const TCPConnPtr &)>;

    using EventCallback=std::function<void()>;

    using ReadEventCallback =std::function<void()>;


}
