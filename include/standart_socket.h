#ifndef SOCKET_CORE
#define SOCKET_CORE

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <filesystem.h>
#include <string_array.h>

using namespace  core::types;
using namespace core::socket;

typedef array<s32> err_buffer;
typedef sockaddr_in   __ssock;
typedef sockaddr       __sock;
typedef socklen_t     __sslen;
typedef __ssock *    __pssock;
typedef __sock *      __psock;
typedef __sslen *    __psslen;

class Socket {
private:
    err_buffer        last_errors;
    u32         reconnect_counter;

public:
    SOCKET _socket(s32);
    s32    _connect(SOCKET, __psock, __sslen, u32 = 0);
    emt    _bind(SOCKET, __psock, __sslen);
    emt    _listen(SOCKET, u32 = backlog);
    SOCKET _accept(SOCKET, __psock = nullptr, __psslen = nullptr);

    emt    _send(SOCKET, string, s32 = 0);
    emt    _sendto(SOCKET, string, __psock, __sslen, u32 = 0);

    string _recv(SOCKET, s32 = 0);
    string _recvfrom(SOCKET, __psock = nullptr, __psslen = nullptr, s32 = 0);

    err_buffer& get_err_buffer() const;
}; // base socks

#endif // SOCKET_CORE
