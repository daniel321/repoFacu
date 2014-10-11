#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

const char* path = "archi.txt";

int main(){
	mknod(path,S_IFIFO|0666,0);		// creo fifo a partir de archivo
	int fd = open(path,O_WRONLY|O_CREAT);	// abro en modo escritura (lo creo si no existe)

	int valor = 25;
	write(fd,&valor,sizeof(int));		// escribo en el pipe

	close(fd);				// cierro archivo
	unlink(path);				// elimino archivo (si el padre no lo elimino antes)
	return 0;
}









