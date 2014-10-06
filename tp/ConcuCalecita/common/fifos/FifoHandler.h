#ifndef FIFOHANDLER_H
#define FIFOHANDLER_H

#include "FifoEscritura.h"
#include "FifoLectura.h"

class FifoHandler {
	public:

	static void escribir(const char* path,int dato){
		FifoEscritura fifo(path);
		fifo.abrir();
		escribir(fifo,dato);
	}

	static void escribir(FifoEscritura fifo,int dato){
		fifo.escribir(&dato,sizeof(int));
	}

	static int leer(const char* path){
		FifoLectura fifo(path);
		fifo.abrir();

		return leer(fifo);
	}

	static int leer(FifoLectura fifo){
		int valor = 0,tam = 0;
		do{
			tam = fifo.leer(&valor,sizeof(int));
		} while(valor == 0 && tam == sizeof(int));
	
		return valor;
	}

};

#endif
