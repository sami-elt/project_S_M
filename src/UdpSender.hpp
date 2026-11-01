#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>

class UdpSender
{
public:
    UdpSender();
    ~UdpSender();

    bool initialize(const std::string& ip, int port);
    bool sendMessage(const std::string& message);

private:
    SOCKET udpSocket;
    sockaddr_in destination;
    bool initialized;
};