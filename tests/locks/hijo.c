#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/file.h>

const char* path = "archi.txt";

void escribir(char valor);

int main(){
	escribir('b');
	return 0;
}

void escribir(char valor){
	int fd = open(path,O_WRONLY|O_APPEND);	// abro en modo escritura
	flock(fd,LOCK_EX);			// bloqueo el archivo

	sleep(2); 				// hago pasar algo de tiempo para ver q no se pisan

	for(int i=0; i<10; i++)			// escribo 10 datos	
		write(fd,&valor,sizeof(char));	
	
	flock(fd,LOCK_UN);			// desbloqueo el archivo
	close(fd);				// cierro el archivo

}











