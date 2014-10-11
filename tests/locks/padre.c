#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/file.h>

const char* path = "archi.txt";

void leer();
void escribir(char valor);

int main(){
	int pid = fork();
	if(pid == 0){
		char** arg = NULL;
		execv("hijo",arg);
	}else{
		escribir('a');
	}

	sleep(1);
	leer();
	return 0;
}

void escribir(char valor){
	int fd = open(path,O_WRONLY|O_APPEND|O_TRUNC);	// abro en modo escritura
	flock(fd,LOCK_EX);				// bloqueo el archivo

	sleep(2); 					// hago pasar algo de tiempo para ver q no se pisan

	for(int i=0; i<10; i++)			// escribo 10 datos	
		write(fd,&valor,sizeof(char));	
	
	flock(fd,LOCK_UN);			// desbloqueo el archivo
	close(fd);				// cierro el archivo

}

void leer(){
	int fd = open(path,O_RDONLY);		// abro en modo lectura 
	flock(fd,LOCK_EX);			// bloqueo el archivo

	printf("\n");
	char dato,tam;
	do{						// imprimo su contenido por pantalla	
		tam = read(fd,&dato,sizeof(char));
		printf("%c",dato);	
	}while((dato != 0)&&(tam == sizeof(char)));
	printf("\n");
	
	flock(fd,LOCK_UN);				// desbloqueo el archivo
	close(fd);					// cierro el archivo
}














