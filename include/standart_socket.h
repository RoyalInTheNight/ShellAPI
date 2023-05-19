#ifndef SOCKET_CORE
#define SOCKET_CORE

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <filesystem.h>
#include <string_array.h>

using namespace  core::types;
using namespace core::socket;

typedef base_string    string;
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
    filesystem            fs_path;

public:
    SOCKET _socket(s32);
    s32    _connect(SOCKET, __psock, __sslen, u32 = 0);
    emt    _bind(SOCKET, __psock, __sslen);
    emt    _listen(SOCKET, u32 = backlog);
    SOCKET _accept(SOCKET, __psock = nullptr, __psslen = nullptr);

    emt    _send(SOCKET, string, s32 = 0);
    emt    _sendfile(SOCKET, fs::path, s32 = 0);

    emt    _sendto(SOCKET, string, __psock, __sslen, u32 = 0);
    emt    _send_file_udp(SOCKET, fs::path, __psock, __sslen, s32 = 0);

    string _recv(SOCKET, s32 = 0);
    emt    _recvfile(SOCKET, fs::path, s32 = 0);

    string _recvfrom(SOCKET, __psock = nullptr, __psslen = nullptr, s32 = 0);
    emt    _recvfile_udp(SOCKET, fs::path, __psock = nullptr, __psslen = nullptr, s32 = 0);

    err_buffer& get_err_buffer() const;
}; // base socks

template<class __sock_t = Socket> class SocketApi : public __sock_t {
private:
    typedef array<__ssock> sock_buffer;
    typedef sock_buffer *  __sock_buff;

    err_buffer       inline_err_buffer;

    typedef struct conn_info {
        SOCKET fd;
        u32  type;
    } *__conn_info;

    __conn_info connections;
    __sock_buff header_conn;

public:
    SocketApi();

    emt InitTCPServer(const string&, const u16, u32);
    emt InitUDPServer(const string&, const u16, u32);

    emt InitTCPConnect(const string&, const u16, u32);
    emt InitUDPConnect(const string&, const u16, u32);

    ~SocketApi();
};

#endif // SOCKET_CORE