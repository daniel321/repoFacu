#ifndef FIFOHANDLER_H
#define FIFOHANDLER_H

#include "FifoEscritura.h"
#include "FifoLectura.h"

class FifoHandler
{
	
public:
	static void escribir(const char* path,int dato);
	static void escribir(FifoEscritura fifo,int dato);
	static int leer(const char* path, bool eliminarTrasLeer = false);
	static int leer(FifoLectura fifo);

};

#endif
