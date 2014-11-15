#include <string>	
#include <unistd.h>	
#include <stdlib.h>	
#include <arpa/inet.h>  
#include <netdb.h>	
#include <stdint.h>
#include <string.h>
#include <vector>
#include <iostream>

using namespace std;

#define TAMBUFFER 50
#define PORT 9999
#define ADDR "127.0.0.1" 

int main(){
	int sockFd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in addr;

	memset(&(addr),0,sizeof(addr));
    	addr.sin_family = AF_INET;
     	addr.sin_port = htons(PORT);
	addr.sin_addr = *((in_addr*)gethostbyname(ADDR)->h_addr);
		
	connect(sockFd,(sockaddr*)&addr,sizeof(addr));


	char buff[15];
	recv(sockFd,buff,15*sizeof(char),0);
	cout << "rcv: " << buff << endl;

	const char buff2[15] = "hi server";
	send(sockFd,buff2,15*sizeof(char),0);
	cout << "send: " << buff2 << endl;

	close(sockFd);
	return 0;
}
