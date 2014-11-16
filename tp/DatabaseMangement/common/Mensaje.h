#ifndef MENSAJE_H
#define MENSAJE_H

#include "Constants.h" 		// tam campos

typedef struct request{
	long mtype;
	char nombre[tamNombre];
	char direccion[tamDir];
	char telefono[tamTel];
	bool leo;
}request;

typedef struct response{
	long mtype;
	char nombre[tamNombre];
	char direccion[tamDir];
	char telefono[tamTel];
}response;

#endif
