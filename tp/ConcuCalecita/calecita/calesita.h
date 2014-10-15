#ifndef CALESITA_H
#define CALESITA_H

#include "../common/fifos/FifoLectura.h"
#include "../common/logger/Logger.h"
#include "../common/Asientos.h"
#include <list>

using namespace std;

class Calesita {

	public:
		static int TiempoDeVuelta;
		static const int TimeoutCalesita = 10;

		Calesita(int NumeroAsientos);
		~Calesita();

		/**
		 * Espera a que haya cierta cantidad de clientes y realiza una vuelta
		 */
		void operar();

		/**
		 * TODO a ser llamada al recibir una señal para cerrar
		 * por parte del administrador de la calesita
		 */
		void cerrar();

	private:
		FifoLectura colaParaEntrar;
		list<int> pids;
		bool abierto;
		Asientos asientos;
		Common::Logger log;
		int numeroAsientos;

		// espera a que aparezca cierta cantidad de clientes para poder arrancar la calesita
		void esperarClientes();

		// da una vuelta e indica a todos los clientes de la calesita que la vuelta transcurrio
		void darVuelta();

};

#endif
















