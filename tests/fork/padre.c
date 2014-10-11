#include <stdio.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>

int main(){
	int pid = fork();

	if(pid == 0){
		char* mens = "hola";
		execv("hijo",&mens);
	}else{
		printf("\nSoy el padre: %d hijo: %d\n",getpid(),pid);
		int retorno;
		waitpid(pid,&retorno,0);

		if(WEXITSTATUS(retorno) == 44)
			printf("\nHijo retorno bien\n\n");
		else
			printf("\nHijo retorno mal\n\n");
	}

	return 0;
}
















