#include <stdio.h>
#include <unistd.h>

int main(){
	int pid = fork();
	if(pid == 0){
		char** arg = NULL;
		execv("hijo",arg);
	}else{
		int signal;
		do{
			printf("\ningrese el numero de señal (0-9): ");
			signal = getchar() - '0';
		}while((signal<0)||(signal>9));
		
		printf("\nmandando señal %d\n",signal);
		kill(pid,signal);
	}

	return 0;
}













