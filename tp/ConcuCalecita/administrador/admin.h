#ifndef ADMIN_H
#define ADMIN_H

#include "../common/logger/Logger.h"
#include "../common/fifos/FifoEscritura.h"
#include "../common/fifos/FifoLectura.h"
#include "../common/SigCerrable.h"

class Administrador : public SigCerrable
{
	public:
		Administrador ();
		/**
		 * Intenta consultar la el dinero de la recaudacion de la calecita
		 */
		void consultarCaja();
	private:
		Common::Logger log;
		FifoEscritura pedirConsulta;
		FifoLectura leerConsulta;

};

#endif
















