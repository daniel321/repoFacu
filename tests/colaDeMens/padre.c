#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <errno.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define TIPO_PADRE 2
#define TIPO_HIJO 1

typedef struct cosito{
	long mtype;
	char frase[30];
	int  numerito;
}cosito;

void imprimir(cosito c);
void inicializarCosito(cosito* c);

int main(){
	int pid = fork();
	if(pid == 0){
		char** arg = NULL;
		execv("hijo",arg);
	}else{
		int id = ftok("Makefile",'d');
		int idCola = msgget(id,IPC_CREAT|0666);

		cosito c;
		
		int tam;
		do{
			tam = msgrcv(idCola,&c,sizeof(cosito)-sizeof(long),TIPO_HIJO,0);
			imprimir(c);
		}while(tam != sizeof(cosito)-sizeof(long));

		inicializarCosito(&c);
		msgsnd(idCola,&c,sizeof(cosito)-sizeof(long),0);

		msgctl(idCola,IPC_RMID,NULL);
	}

	return 0;
}

void imprimir(cosito c){
	printf("\nPadre recibe: ");
	printf("\nfrase: %s",c.frase);
	printf("\nnumero: %d\n",c.numerito);
}

void inicializarCosito(cosito* c){
	c->mtype = TIPO_PADRE;
	c->numerito = 66;
	char frase[30] = "chau!!";
	strncpy(c->frase, frase, sizeof(c->frase));
}










