CC=protoc
CFLAGS=-c -DSTRICT -G3 -Ow -W3 -Zp -Tp
CFLAGSMT=--go_out=. 
LINKER=go
GUILIBS=-lcrypto
GUIFLAGS=build
json_c: t1.pb/t1.pb.go json_c.go
	$(LINKER) $(GUIFLAGS)  json_c.go

t1.pb/t1.pb.go: t1.pb/t1.proto
	cd t1.pb
	$(CC) $(CFLAGSMT) t1.proto
	cd ..