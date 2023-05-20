#include <liburing_socket.h>

SOCKET Socket::_socket(s32 l4_protocol) {
    switch (l4_protocol) {
        case IPPROTO_TCP:
            return socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        case IPPROTO_UDP:
            return socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        default:
            return NULL;
    }
}

s32 Socket::_connect(SOCKET fd, __psock client_sock, __sslen client_sock_len, s32 reconnect_count) {
    __ring ring     = new io_uring();
    __params params = new io_uring_params();
    __sqe sqe;
    __cqe cqe;

    if (io_uring_queue_init(32, ring, params) < 0) {
        last_errors.push_back(io_queue_error);

        return io_queue_error;
    }

    sqe = io_uring_get_sqe(ring);

    io_uring_prep_connect(sqe, fd, client_sock, client_sock_len);
    io_uring_sumbit(ring);

    io_uring_wait_cqe(ring, *cqe);
    io_uring_cqe_seen(ring, cqe);

    s32 ret = cqe->res;

    io_uring_queue_exit(ring);

    if (ret == -115) {
        if (reconnect_count > 0)
            this->_connect(fd, client_sock, client_sock_len, reconnect_count--);

        last_errors.push_back(connect_error);

        return connect_error;
    }
}