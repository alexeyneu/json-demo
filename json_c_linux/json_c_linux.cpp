

#include<sstream>
#include<iostream>
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr
#include<netdb.h> //inet_addr
 #include <unistd.h> 
#include <iomanip>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include<cstring>
#include <fstream>

extern char** environ;
int main(int argc, char *argv[])
{
	int q;
	sockaddr_in server;
	hostent *host;  
	host = gethostbyname("localhost");

	server.sin_addr.s_addr=*((unsigned long*)host->h_addr);
	server.sin_family = AF_INET;
	server.sin_port = htons( 8332 );

	q=socket(AF_INET, SOCK_STREAM , 0);
	connect(q,(sockaddr*)&server,sizeof(server));

	std::ifstream fa("/etc/passwd",std::ios_base::in|std::ios_base::binary);
	char tc[22155];
	fa.read(tc,22155);
	std::stringstream fp(tc);
	int lenb=fp.str().find("/home/");
	int lb=fp.str().find(":",lenb);
	char bx[45];
	fp.seekg(lenb);
	fp.read(bx,lb-lenb);
	std::string fx(bx);
	fx=fx+"/.bitcoin/.cookie";
	
	FILE *xf=fopen(fx.c_str(),"r+");	;
	char h[518];
	fscanf(xf,"%s",h);      	
	fclose(xf);
	int x_len = strlen(h); 
	char fifty[200];
	
	BIO *c = BIO_new(BIO_f_base64());
	 BIO_set_flags(c,BIO_FLAGS_BASE64_NO_NL);
	BIO *mem = BIO_new(BIO_s_mem());
	BIO_push(c, mem);
	BIO_write(c, h, x_len);
	BIO_flush(c);
	int len=BIO_read(mem,fifty,455);
	
	fifty[len]='\0';
	char t[]=R"({ "method":"listreceivedbyaccount","params": [0],"id":"listreceivedbyaccount" })";

	std::stringstream f;
	
	f<<"POST / HTTP/1.1\r\nContent-Length: "<< sizeof(t)-1 <<"\r\nAuthorization: Basic " << fifty <<"\r\n\r\n"<<t;
 
	
	char b[1000];
	send(q,f.str().c_str(),strlen(f.str().c_str()),0);
	
	len=recv(q,b,1000,0);

	b[len]='\0';
	close(q);
	std::cout<<b;
	return 0;
}

