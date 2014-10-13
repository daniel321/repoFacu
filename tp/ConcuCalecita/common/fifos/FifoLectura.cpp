#include "FifoLectura.h"

#include "../exception/ErrnoWrap.h"

FifoLectura::FifoLectura(const std::string nombre) : Fifo(nombre) {}

FifoLectura::~FifoLectura() {}

void FifoLectura::abrir() {
	fd = ::open( nombre.c_str(),O_RDONLY );
	if (fd == -1) throw Common::ErrnoWrap("Error al abrir fifo.");
}

ssize_t FifoLectura::leer(void* buffer,const ssize_t buffsize) const {
	int ret = ::read ( fd,buffer,buffsize );
	if (ret == -1) throw Common::ErrnoWrap("Error al leer de fifo.");
	return ret;
}
