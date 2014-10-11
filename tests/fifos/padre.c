#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

const char* path = "archi.txt";

int main(){
	int pid = fork();
	if(pid == 0){
		char* mens = "hola";
		execv("hijo",&mens);
	}else{
		mknod(path,S_IFIFO|0666,0);			// creo fifo a partir de archivo
		int fd = open(path,O_RDONLY|O_CREAT);		// abro en modo lectura (lo creo si no existe)

		int valor,tam;
		do{
			tam = read(fd,&valor,sizeof(int));	// leo del pipe de lectura
		}while((valor == 0) || (tam != sizeof(int)));
		
		printf("\nval: %d\n",valor);

		close(fd);					// cierro archivo
		unlink(path);					// elimino archivo (si el hijo no lo elimino antes)
	}

	return 0;
}
