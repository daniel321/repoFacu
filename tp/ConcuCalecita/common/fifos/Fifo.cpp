#include "Fifo.h"

#include "../exception/ErrnoWrap.h"
#include <errno.h>
#include <iostream>

Fifo::Fifo(const std::string nombre) : nombre(nombre), fd(-1)
{
	int ret = ::mknod ( nombre.c_str(),S_IFIFO|0666,0 );
	if (ret == -1 && errno != EEXIST) throw Common::ErrnoWrap("Error al crear fifo.");
}

Fifo::~Fifo() {}

void Fifo::cerrar() {
	if (fd != -1)
	{
		int ret = ::close ( fd );
		if (ret == -1) throw Common::ErrnoWrap("Error al cerrar fifo.");
		fd = -1;
	}
}

void Fifo::eliminar()
{
	cerrar();
	int ret = ::unlink ( nombre.c_str() );
	if (ret == -1) throw Common::ErrnoWrap("Error al eliminar fifo.");
}
