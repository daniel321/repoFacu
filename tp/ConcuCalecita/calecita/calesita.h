#ifndef CALESITA_H
#define CALESITA_H

#include "../common/fifos/FifoLectura.h"
#include "../common/fifos/FifoEscritura.h"
#include "../common/logger/Logger.h"
#include "../common/Asientos.h"
#include "../common/signals/BoolHandler.h"
#include "../common/signals/VoidHandler.h"
#include <list>

using namespace std;

class Calesita {

	public:
		static const int TimeoutCalesita = 10;
		Calesita(int NumeroAsientos, int tiempoVuelta);
		~Calesita();
		/**
		 * Espera a que haya cierta cantidad de clientes y realiza una vuelta
		 */
		void operar();
	private:
		FifoLectura colaParaEntrar;
		FifoEscritura antiEof; // Para mantener el extremo del fifo abierto
		list<int> pids;
		Asientos asientos;
		Common::Logger log;
		int numeroAsientos;
		int tiempoVuelta;
		VoidHandler alarmHandler;
		BoolHandler quitHandler;

		// espera a que aparezca cierta cantidad de clientes para poder arrancar la calesita
		void esperarClientes();

		// da una vuelta e indica a todos los clientes de la calesita que la vuelta transcurrio
		void darVuelta();

};

#endif
















