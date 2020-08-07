CC=c++ -c
CFLAGS=-c -DSTRICT -G3 -Ow -W3 -Zp -Tp
CFLAGSMT=-std=c++11 
LINKER=c++
GUILIBS=-lcrypto

CXX 			= c++ -c
CXXFLAGS		= -std=c++17 -O3
LIBS			= -ltbb -lpthread
LFLAGS			= 
LINKER			= c++



json_c: f.o
	$(LINKER) $(LFLAGS)  f.o  $(LIBS) -o t

json_c_linux.o: f.cpp
	$(CXX) $(CXXFLAGS) f.cpp

