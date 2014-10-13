#include "FifoEscritura.h"

#include "../exception/ErrnoWrap.h"
#include <sys/file.h>

FifoEscritura::FifoEscritura(const std::string nombre) : Fifo(nombre) {}

FifoEscritura::~FifoEscritura() {}

void FifoEscritura::abrir() {
	fd = ::open ( nombre.c_str(),O_WRONLY );
	if (fd == -1) throw Common::ErrnoWrap("Error al abrir fifo para escritura.");
}

void FifoEscritura::escribir(const void* buffer,const ssize_t buffsize) const
{
	int retorno = ::write(fd, buffer, buffsize);
	if (retorno == -1) throw Common::ErrnoWrap("Error al escribir en fifo.");
}
