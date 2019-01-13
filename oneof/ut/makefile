CC=protoc
CFLAGS=-c -DSTRICT -G3 -Ow -W3 -Zp -Tp
CFLAGSMT=--go_out=. 
LINKER=go
GUILIBS=-lcrypto
GUIFLAGS=build
x: t1.pb/t1.pb.go sample.go
	$(LINKER) $(GUIFLAGS)  sample.go

t1.pb/t1.pb.go: t1.pb/t1.proto
	cd t1.pb ;\
	$(CC) $(CFLAGSMT) ./t1.proto
	cd ..