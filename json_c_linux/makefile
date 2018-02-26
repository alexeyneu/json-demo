CC=c++ -c
CFLAGS=-c -DSTRICT -G3 -Ow -W3 -Zp -Tp
CFLAGSMT=-std=c++11 
LINKER=c++
GUILIBS=-lcrypto

 json_c: json_c_linux.o
	$(LINKER) $(GUIFLAGS)  json_c_linux.o  $(GUILIBS) -o json_c

 json_c_linux.o: json_c_linux.cpp
	$(CC) $(CFLAGSMT) json_c_linux.cpp

