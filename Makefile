CXX=g++
CC=gcc

SRC_FS_COMPILE=src/filesystem.cpp -o fs.o
SRC_SS_COMPILE=src/standart_socket.cpp -o ssnet.o

STATIC_LIB_FS=ar rc libfs.a fs.o
STATIC_LIB_SS=ar rc libssnet.a ssnet.o

STANDART=-std=gnu++17

lib:
	$(CXX) -c -I./include/ $(SRC_FS_COMPILE) $(STANDART)
	$(STATIC_LIB_FS)

	$(CXX) -c -I./include/ $(SRC_SS_COMPILE) $(STANDART)
	$(STATIC_LIB_SS)

	rm *.o

test:
	$(CXX) -I./include/ tests/test_array.cpp -o tarray.out $(STANDART)
	$(CXX) -I./include/ -L. tests/test_filesystem.cpp -o tfs.out -lfs $(STANDART)
	$(CXX) -I./include/ -L. tests/test_socket_client.cpp -o tssnetc.out -lfs -lssnet $(STANDART)
	$(CXX) -I./include/ -L. tests/test_socket_server.cpp -o tssnets.out -lfs -lssnet $(STANDART)

clear:
	rm *.a
	rm tarray.out
	rm tfs.out
	rm tssnetc.out
	rm tssnets.out
