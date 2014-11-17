#include "ErrnoWrap.h"

#include <cstring>
#include <errno.h>

namespace Common
{

ErrnoWrap::ErrnoWrap() : mensaje(0)
{
	mensaje = new char[strlen(strerror(errno))+1];
	strcpy(this->mensaje, strerror(errno));
}

ErrnoWrap::ErrnoWrap(const char* mensaje) : mensaje(0)
{
	int errLen = strlen(strerror(errno));
	this->mensaje = new char[errLen + strlen(mensaje)+2];
	strcpy(this->mensaje, strerror(errno));
	this->mensaje[errLen] = ':';
	strcpy(this->mensaje + errLen + 1, mensaje);
}

ErrnoWrap::~ErrnoWrap() throw()
{
	if (mensaje != 0) delete[] mensaje;
}

const char* ErrnoWrap::what() const throw()
{
	return mensaje;
}



} /* namespace Common */
