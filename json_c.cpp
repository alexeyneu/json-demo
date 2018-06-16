#include <iostream>
#include <WinSock2.h>
#include <atlenc.h>
#include <sstream>
#include <fstream>
#pragma comment(lib, "ws2_32")
int wmain(int argc, wchar_t* argv[])
{
	WSADATA fc;
	WSAStartup(0x202,&fc); //sockets 2.02 ,hibyte and lobyte = 2 
	hostent *host = gethostbyname("localhost");
	sockaddr_in server = { AF_INET , htons(8556) /* btx port */ , *(in_addr*)(unsigned long*)host->h_addr };
	SOCKET q = socket(AF_INET, SOCK_STREAM , 0);
	connect(q,(sockaddr*)&server,sizeof(server));
	wchar_t w[140];
	ExpandEnvironmentStrings(L"%APPDATA%\\Bitcore\\.cookie",w,140); //btx password access
	std::ifstream fa(w);  
	std::string h;
	fa>>h; // pwd done
	char fifty[200]={}, b[1000]={};
	int len=Base64EncodeGetRequiredLength(h.length());
	Base64Encode((BYTE *)h.c_str(), h.length(), fifty, &len, ATL_BASE64_FLAG_NOCRLF); // password is ready for http 
	char t[]="{ \"method\":\"listreceivedbyaccount\",\"params\": [0],\"id\":\"listreceivedbyaccount\" }"; //json part of request 
	std::stringstream f;
	f<<"POST / HTTP/1.1\r\nContent-Length: "<< sizeof(t)-1 <<"\r\nAuthorization: Basic " << fifty <<"\r\n\r\n"<<t; //full request to json server 
	send(q,f.str().c_str(), f.str().length() ,0); //gone
	recv(q,b,1000,0); 
	closesocket(q);
	std::cout<<b; 
	return 0;
}
