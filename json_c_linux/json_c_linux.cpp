#include<sys/socket.h>    //socket
#include<netdb.h> 
#include <cstdint>
#include <iostream>
#include <sstream>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <fstream>
#include <unistd.h>
int main(int argc, char *argv[])
{
  	int q;
  	hostent *host = gethostbyname("localhost"); 	
	sockaddr_in server = { AF_INET , htons( 8332 ) /* btc port */ , *((unsigned long*)host->h_addr) };
	q=socket(AF_INET, SOCK_STREAM , 0);
	connect(q,(sockaddr*)&server,sizeof(server));
	std::fstream fa("/etc/passwd",std::ios_base::in|std::ios_base::binary);
	std::stringstream mj;
	fa>>mj.rdbuf();     
	int lenb=mj.str().find("/home/");
	int lb=mj.str().find(":",lenb);
	std::string fx(mj.str(),lenb,lb-lenb);
	std::ifstream fc(fx+"/.bitcoin/.cookie");
	std::string h;
	fc>>h;
	char fifty[200]={};
	BIO *c = BIO_new(BIO_f_base64());
	 BIO_set_flags(c,BIO_FLAGS_BASE64_NO_NL);
	BIO *mem = BIO_new(BIO_s_mem());
	BIO_push(c, mem);
	BIO_write(c,h.c_str(),h.length());
	BIO_flush(c);
	BIO_read(mem,fifty,455);
	char t[]=R"({ "method":"listreceivedbyaccount","params": [0],"id":"listreceivedbyaccount" })";
	std::stringstream f;
	f<<"POST / HTTP/1.1\r\nContent-Length: "<< sizeof(t)-1 <<"\r\nAuthorization: Basic " << fifty <<"\r\n\r\n"<<t;
	char b[1000]={};
	send(q,f.str().c_str(),f.str().length(),0);
	recv(q,b,1000,0);
	close(q);
	std::cout<<b;
	return 0;
}
