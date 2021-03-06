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
#define BAGLOAD 5

int main(){
	int sockFd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in addr;

	memset(&(addr),0,sizeof(addr));
    	addr.sin_family = AF_INET;
     	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = INADDR_ANY;
		
	bind(sockFd,(sockaddr*)&addr,sizeof(addr));
	listen(sockFd,BAGLOAD);

	struct sockaddr_in cliaddr;
	socklen_t tamcli = sizeof(cliaddr);
	int cliFd = accept(sockFd,(sockaddr*)&cliaddr,&tamcli);

	const char buff[15] = "hi client";
	send(cliFd,buff,15*sizeof(char),0);
	cout << "send: " << buff << endl;

	char buff2[15];
	recv(cliFd,buff2,15*sizeof(char),0);
	cout << "recv: " << buff2 << endl;

	close(cliFd);
	close(sockFd);
	return 0;
}


