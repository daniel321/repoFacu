#include "FifoLectura.h"

#include "../exception/ErrnoWrap.h"
#include "../exception/InterruptException.h"
#include "../exception/ExEOF.h"
#include <errno.h>

FifoLectura::FifoLectura(const std::string nombre) : Fifo(nombre) {}

FifoLectura::~FifoLectura() {}

void FifoLectura::abrir() {
	if (fd == -1) fd = ::open( nombre.c_str(),O_RDONLY );
	if (fd == -1)
	{
		if (errno == EINTR) throw Common::InterruptException();
		throw Common::ErrnoWrap("Error al abrir fifo de lectura.");
	}
}

void FifoLectura::leer(void* buffer,const ssize_t buffsize) const {
	int ret = ::read ( fd,buffer,buffsize );
	if (ret == -1)
	{
		if (errno == EINTR) throw Common::InterruptException();
		throw Common::ErrnoWrap("Error al leer de fifo.");
	}
	if (ret == 0) throw Common::ExEOF();
}
