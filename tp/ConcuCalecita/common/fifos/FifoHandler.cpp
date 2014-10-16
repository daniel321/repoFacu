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

int FifoHandler::leer(const char* path, bool eliminarTrasLeer){
	FifoLectura fifo(path);
	fifo.abrir();
	int dato = leer(fifo);
	if (eliminarTrasLeer)
	{
		fifo.cerrar();
		fifo.eliminar();
	}
	return dato;
}

int FifoHandler::leer(FifoLectura fifo){
	int valor;
	fifo.leer(&valor,sizeof(int));
	return valor;
}

