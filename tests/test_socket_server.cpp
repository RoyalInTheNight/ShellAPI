#include <standart_socket.h>

s32 main() {
    Socket sock;
    sockaddr_in sock1;

    sock1.sin_addr.s_addr = htonl(INADDR_ANY);
    sock1.sin_port        = htons(4444);
    sock1.sin_family      = AF_INET;

    SOCKET fd = sock._socket(IPPROTO_TCP);

    sock._bind(fd, (sockaddr *)&sock1, sizeof(sock1));
    sock._listen(fd);

    SOCKET fd1 = sock._accept(fd);

    string str = sock._recv(fd1);

    for (u32 i = 0; i < str.size(); i++)
        std::cout << str[i];
}