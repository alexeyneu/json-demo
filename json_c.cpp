#include <cstdint>
#include <iostream>
#include <WinSock2.h>
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit
#include <atlenc.h>
#include <sstream>
#include <fstream>

#pragma comment(lib, "ws2_32")

int wmain(int argc, wchar_t* argv[])
{
	WSADATA fc;
	WSAStartup(0x202,&fc); //sockets 2.02 ,hibyte and lobyte = 2 
	SOCKET q;
	sockaddr_in server;
  //	sockaddr_in ;
	hostent *host;  
	host = gethostbyname("localhost");

	server.sin_addr.s_addr=*((unsigned long*)host->h_addr);
	server.sin_family = AF_INET;
	server.sin_port = htons( 8556 ); // btx port

	q=socket(AF_INET, SOCK_STREAM , 0);
	connect(q,(sockaddr*)&server,sizeof(server));
	
	wchar_t w[140];
	ExpandEnvironmentStrings(L"%APPDATA%\\Bitcore\\.cookie",w,140);
	std::ifstream fa(w);  
	std::string h;
	fa>>h;

	char fifty[200]={};
	int len=Base64EncodeGetRequiredLength(h.length());
	Base64Encode((BYTE *)h.c_str(),h.length(),fifty,&len,ATL_BASE64_FLAG_NOCRLF);
	char t[]="{ \"method\":\"listrece\
ivedbyaccount\",\"params\": [0],\"id\":\"listreceivedbyaccount\" }\r\n";

	std::stringstream f;
	
	f<<"POST / HTTP/1.1\r\nContent-Length: "<< sizeof(t)-1 <<"\r\nAuthorization: Basic " << fifty <<"\r\n\r\n"<<t;
 
	
	char b[1000];
	send(q,f.str().c_str(),f.str().length(),0);
	
	len=recv(q,b,1000,0);

	b[len]='\0';
	closesocket(q);
	std::cout<<b;
	return 0;
}

