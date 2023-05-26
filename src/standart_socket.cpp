#include <standart_socket.h>
#include <unistd.h>

using namespace core::socket::errors;

SOCKET Socket::_socket(s32 l3_protocol) {
    switch (l3_protocol) {
        case IPPROTO_TCP:
            last_errors.push_back(ok);
            return socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        case IPPROTO_UDP:
            last_errors.push_back(ok);
            return socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        default:
            last_errors.push_back(invalid_socket);
            return NULL;
    }
}

s32 Socket::_connect(SOCKET fd, __psock sock, __sslen socklen, u32 reconnect) {
    if (connect(fd, sock, socklen) < 0) {
        if (reconnect != 0 && reconnect < reconnect_counter) {
            sleep(5); 

            reconnect_counter++;

            this->_connect(fd, sock, socklen, reconnect);
        }

        last_errors.push_back(connect_error);

        if (reconnect == reconnect_counter)
            return connect_error;
    }
    
    else {
        last_errors.push_back(ok);

        return ok;
    }
}

emt Socket::_bind(SOCKET fd, __psock sock, __sslen socklen) {
    if (bind(fd, sock, socklen) < 0)
        last_errors.push_back(bind_error);

    else
        last_errors.push_back(ok);
}

emt Socket::_listen(SOCKET fd, u32 queue) {
    if (listen(fd, queue) < 0)
        last_errors.push_back(listen_error);

    else
        last_errors.push_back(ok);
}

SOCKET Socket::_accept(SOCKET fd, __psock clsock, __psslen clsocklen) {
    SOCKET fd_ret = 0;

    if ((fd_ret = accept(fd, clsock, clsocklen)) < 0) {
        last_errors.push_back(invalid_socket);

        return invalid_socket;
    }

    else {
        last_errors.push_back(ok);

        return fd_ret;
    }
}

emt Socket::_send(SOCKET fd, string message, s32 flag) {
    if (send(fd, message.data(), message.size(), flag) < 0)
        last_errors.push_back(send_error);
    
    else
        last_errors.push_back(ok);
}

emt Socket::_sendto(SOCKET fd, string message, __psock client_sock, __sslen client_sock_len, u32 flag) {
    if (sendto(fd, message.data(), message.size(), flag, client_sock, client_sock_len) < 0)
        last_errors.push_back(send_error);
    
    else
        last_errors.push_back(ok);
}

string Socket::_recv(SOCKET fd, s32 flag) {
    s8 message_buffer[max_message_len];
    string str_buffer;
    
    while (1) {
        s32 size_message = recv(fd, message_buffer, max_message_len, flag);

        if (size_message <= 0) {
            last_errors.push_back(recv_error);

            break; 
        } 
        
        else {
            str_buffer += message_buffer;

            for (u32 i = 0; i < size_message; i++)
                message_buffer[i] = 0;

            last_errors.push_back(ok);
        }
    }

    return str_buffer;
}

string Socket::_recvfrom(SOCKET fd, __psock client_sock, __psslen client_sock_len, s32 flag) {
    s8 message_buffer[max_message_len];
    string str_buffer;

    while (1) {
        s32 size_message = recvfrom(fd, message_buffer, sizeof(message_buffer), flag, client_sock, client_sock_len);

        if (size_message <= 0) {
            last_errors.push_back(recv_error);

            break;
        }

        else {
            str_buffer += message_buffer;

            for (u32 i = 0; i < size_message; i++)
                message_buffer[i] = 0;

            last_errors.push_back(ok);
        }
    }

    return str_buffer;
}