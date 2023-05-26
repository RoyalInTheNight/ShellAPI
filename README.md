# SHELL_API
## guide
`to develop`


## bugs
(solved) linking error when building the network part of the application:
```
/usr/bin/ld: ./libssnet.a(ssnet.o): in function `Socket::_sendfile(int, std::filesystem::__cxx11::path, int)':
standart_socket.cpp:(.text+0x32c): undefined reference to `filesystem::file_read(std::filesystem::__cxx11::path)'
/usr/bin/ld: ./libssnet.a(ssnet.o): in function `Socket::_send_file_udp(int, std::filesystem::__cxx11::path, sockaddr*, unsigned int, int)':
standart_socket.cpp:(.text+0x50f): undefined reference to `filesystem::file_read(std::filesystem::__cxx11::path)'
/usr/bin/ld: ./libssnet.a(ssnet.o): in function `Socket::_recvfile(int, std::filesystem::__cxx11::path, int)':
standart_socket.cpp:(.text+0x7d2): undefined reference to `filesystem::file_write(std::filesystem::__cxx11::path, base_string)'
/usr/bin/ld: ./libssnet.a(ssnet.o): in function `Socket::_recvfile_udp(int, std::filesystem::__cxx11::path, sockaddr*, unsigned int*, int)':
standart_socket.cpp:(.text+0xa7a): undefined reference to `filesystem::file_write(std::filesystem::__cxx11::path, base_string)'
collect2: error: ld returned 1 exit status
make: *** [Makefile:24: test] Error 1
```
when using a operator `arr& operator+=(arr&)` when using an oparator, there is a problem of data collision when adding new data:

```
[work@DESKTOP-SK7Q9NK ShellAPI]$ ./tarray.out 
23 24 25 26 27 28 29 30 31 32 
23 24 25 26 27 28 29 30 31 

23 24 25 26 27 28 29 30 31 
25 26 27 28 29 30 31 32 33 34 -715647369 22069 -1706704218 802963765 27 28 29 30 31
```

broken data reception through the network
