#include <stdio.h>
#include <unistd.h>

int main(){
	int pipeFd[2];
	pipe(pipeFd);

	int pid = fork();
	if(pid == 0){
		close(pipeFd[0]);					// cierro pipe lectura
		int valor = 25;	
		write(pipeFd[1],&valor,sizeof(int));			// escribo en pipe de escritura
		close(pipeFd[1]);					// cierro pipe escritura
	}else{
		close(pipeFd[1]);					// cierro pipe escritura

		int valor,tam;
		do{
			tam = read(pipeFd[0],&valor,sizeof(int));	// leo del pipe de lectura
		}while((valor == 0) || (tam != sizeof(int)));

		printf("\nvalor: %d\n",valor);
		close(pipeFd[0]);					// cierro pipe lectura
	}

	return 0;
}















