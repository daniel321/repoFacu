#include "FifoHandler.h"
#include "FifoEscritura.h"
#include "FifoLectura.h"

void FifoHandler::escribir(const char* path,int dato){
	FifoEscritura fifo(path);
	fifo.abrir();
	escribir(fifo,dato);
}

void FifoHandler::escribir(FifoEscritura fifo,int dato){
	fifo.escribir(&dato,sizeof(int));
}

int FifoHandler::leer(const char* path){
	FifoLectura fifo(path);
	fifo.abrir();
	return leer(fifo);
}

int FifoHandler::leer(FifoLectura fifo){
	int valor = 0,tam = 0;
	do{
		tam = fifo.leer(&valor,sizeof(int));
	} while(tam != sizeof(int));

	return valor;
}

