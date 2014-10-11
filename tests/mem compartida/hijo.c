#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(){
	int clave = ftok("padre.c",1);
	int segmento = shmget(clave,sizeof(int),0666|IPC_CREAT);
	int* varCompartida = (int*) shmat(segmento,NULL,0);

	printf("\nleo Variable: %d\n\n",*varCompartida);
	return 0;
}












