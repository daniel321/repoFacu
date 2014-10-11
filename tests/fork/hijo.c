#include <stdio.h>
#include <stdlib.h>
int main(int argc, char** argv){
	printf("\nSoy el hijo: %d padre: %d\n",getpid(),getppid());
	printf("mensaje: %s \n\n",argv[0]);

	exit(44);
}














