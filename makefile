CC=cl -c
CFLAGS= -O2 -DSTRICT  -D_UNICODE -DUNICODE -Ow -W3 -Tp
CFLAGSMT=
LINKER=link
GUILIBS=/NXCOMPAT /MACHINE:X64 /ERRORREPORT:NONE /ENTRY:wmainCRTStartup

k.exe : json_c.obj
	$(LINKER) $(GUILIBS) json_c.obj   


json_c.obj :json_c.cpp
	$(CC) $(CFLAGS) json_c.cpp


