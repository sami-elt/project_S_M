#include "UdpSender.hpp"

UdpSender::UdpSender()
{
    udpSocket = INVALID_SOCKET;
    initialized = false;
}

UdpSender::~UdpSender()
{
    if (udpSocket != INVALID_SOCKET)
    {
        closesocket(udpSocket);
    }

    WSACleanup();
}
bool UdpSender::initialize(const std::string& ip, int port)
{
    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        return false;
    }

    udpSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (udpSocket == INVALID_SOCKET)
    {
        return false;
    }

    destination = {};
    destination.sin_family = AF_INET;
    destination.sin_port = htons(port);

    if (inet_pton(AF_INET, ip.c_str(), &destination.sin_addr) != 1)
    {
        return false;
    }

    initialized = true;
    return true;
}
bool UdpSender::sendMessage(const std::string& message)
{
    if (!initialized)
    {
        return false;
    }

    int result = sendto(
        udpSocket,
        message.c_str(),
        static_cast<int>(message.size()),
        0,
        reinterpret_cast<sockaddr*>(&destination),
        sizeof(destination)
    );

    return result != SOCKET_ERROR;
}