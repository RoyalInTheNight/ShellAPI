#ifndef LIBURING_SOCKET
#define LIBURING_SOCKET

#include <string_array.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <liburing.h>

using namespace core::types;
using namespace core::socket;
using namespace core::socket::errors;
using namespace core::socket::liburing_errors;

typedef base_string    string;
typedef array<s32> err_buffer;
typedef sockaddr_in   __ssock;
typedef sockaddr       __sock;
typedef socklen_t     __sslen;
typedef __ssock *    __pssock;
typedef __sock *      __psock;
typedef __sslen *    __psslen;

typedef io_uring_sqe *      __sqe;
typedef io_uring_cqe *      __cqe;
typedef io_uring_params *__params;
typedef io_uring *         __ring;

class Socket {
private:
    err_buffer    last_errors;
    u32     reconnect_counter;

    __cqe       cqes[backlog];

public:
    SOCKET _socket(s32);
    s32    _connect(SOCKET, __psock, __sslen, u32 = 0);
    emt    _bind(SOCKET, __psock, __sslen);
    SOCKET _accept(SOCKET, __psock = nullptr, __psslen = nullptr);

    emt    _send(SOCKET, string, s32 = 0);
    emt    _sendto(SOCKET, string, __psock, __sslen, s32 = 0);

    string _recv(SOCKET, s32 = 0);
    string _recvfrom(SOCKET, __psock, __psslen, s32 = 0);
}

#endif // LIBURING_SOCKET
