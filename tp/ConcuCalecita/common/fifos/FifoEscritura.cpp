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
	//TODO: Evaluar si este lockeo es realmente necesario en los casos que el write escriba "cortado"
	int lockResult = ::flock(fd, LOCK_EX);
	if (lockResult == -1) throw Common::ErrnoWrap("Error al escribir en fifo.");
	ssize_t retorno = 0;
	ssize_t faltaEscribir = buffsize;
	while (faltaEscribir > 0)
	{
		retorno = ::write(fd, (char*)(buffer + buffsize - faltaEscribir), buffsize);
		if (retorno == -1) throw Common::ErrnoWrap("Error al escribir en fifo.");
		faltaEscribir -= retorno;
	}
	lockResult = ::flock(fd, LOCK_UN);
	if (lockResult == -1) throw Common::ErrnoWrap("Error al escribir en fifo.");
}
