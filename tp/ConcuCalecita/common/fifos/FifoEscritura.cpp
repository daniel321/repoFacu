#include "FifoEscritura.h"

#include "../exception/ErrnoWrap.h"
#include "../exception/InterruptException.h"
#include "../exception/ExEOF.h"
#include <sys/file.h>
#include <errno.h>

FifoEscritura::FifoEscritura(const std::string nombre) : Fifo(nombre) {}

FifoEscritura::~FifoEscritura() {}

void FifoEscritura::abrir() {
	if (fd == -1) fd = ::open ( nombre.c_str(),O_WRONLY );
	if (fd == -1)
	{
		if (errno == EINTR) throw Common::InterruptException();
		throw Common::ErrnoWrap("Error al abrir fifo de escritura.");
	}
}

void FifoEscritura::escribir(const void* buffer,const ssize_t buffsize) const
{
	int retorno = ::write(fd, buffer, buffsize);
	if (retorno == -1) throw Common::ErrnoWrap("Error al escribir en fifo.");
	if (retorno == 0) throw Common::ExEOF();
}
