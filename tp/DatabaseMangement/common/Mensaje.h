#ifndef MENSAJE_H
#define MENSAJE_H

#include "Registro.h"

typedef struct request{
	long mtype;
	struct registro reg;
	bool leo;
}request;

typedef struct response{
	long mtype;
	struct registro reg;
}response;

#endif
