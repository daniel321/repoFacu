#include <stdio.h>
#include <string.h>

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
	int id = ftok("Makefile",'d');
	int idCola = msgget(id,IPC_CREAT|0666);

	cosito c;
	inicializarCosito(&c);

	msgsnd(idCola,&c,sizeof(cosito)-sizeof(long),0);

	int tam;
	do{
		tam = msgrcv(idCola,&c,sizeof(cosito)-sizeof(long),TIPO_PADRE,0);
		imprimir(c);
	}while(tam != sizeof(cosito)-sizeof(long));

	msgctl(idCola,IPC_RMID,NULL);
	return 0;
}


void imprimir(cosito c){
	printf("\nhijo recibe: ");
	printf("\nfrase: %s",c.frase);
	printf("\nnumero: %d\n\n",c.numerito);
}

void inicializarCosito(cosito* c){
	c->mtype = TIPO_HIJO;
	c->numerito = 55;
	char frase[30] = "hola!!";
	strncpy(c->frase, frase, sizeof(c->frase));
}






