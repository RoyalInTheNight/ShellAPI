#include <standart_socket.h>


s32 main() {
    Socket sock;
    sockaddr_in sock1;

    sock1.sin_addr.s_addr = inet_addr("127.0.0.1");
    sock1.sin_port        = htons(4444);
    sock1.sin_family      = AF_INET;

    SOCKET fd = sock._socket(IPPROTO_TCP);

    sock._connect(fd, (sockaddr *)&sock1, sizeof(sock1));

    base_string str = "Message delivered!!!\n";

    sock._send(fd, str);
}