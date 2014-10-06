#ifndef CALESITA_H
#define CALESITA_H

#include <list>
#include <ctime>					// clock
#include <signal.h>					// kill

#include "../common/Constants.h" 			// archivo,code
#include "../common/fifos/FifoHandler.h"
#include "../common/fifos/FifoLectura.h"
#include "../common/logger/Logger.h"

const char archLog[] = "logs/logCalesita";

using namespace std;

class Calesita {

	public:
		Calesita();
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
		Common::Logger log;

		// espera a que aparezca cierta cantidad de clientes para poder arrancar la calesita
		void esperarClientes();

		// da una vuelta e indica a todos los clientes de la calesita que la vuelta transcurrio
		void darVuelta();

		// TODO a ser llamado por un timeout
		void arrancarVueltaPrematuramente();
};

// constructor
Calesita::Calesita() : colaParaEntrar(ARCHCOLACSUBIRSEALACALECITA), abierto(true), log(archLog)
{
	colaParaEntrar.abrir();
}	

// destructor
Calesita::~Calesita(){
	log << "Calesita cerrando." << endl;
}	

// espera a que haya cierta cantidad de clientes y realiza una vuelta
void Calesita::operar(){
	do{
		log << "Calesita esperando que llegue mas gente." << endl;
		esperarClientes();
		// TODO reset timeout
		log << "Calesita dando una vuelta con " << pids.size() << " pasajeros." << endl;
		darVuelta();
		log << "Calesita termino de dar la vuelta." << endl;
	}while(abierto);

	if(pids.size() > 0){
		log << "Calesita dando una vuelta con " << pids.size() << " pasajeros." << endl;
		darVuelta();
		log << "Calesita termino de dar la vuelta." << endl;
	}

}

// espera a que aparezca cierta cantidad de clientes para poder arrancar la calesita
void Calesita::esperarClientes(){
	do{
		int pid = FifoHandler::leer(colaParaEntrar);

		if(pid != 0) {
			kill(pid,SIGNALCLIENTECALECITA);
			pids.push_back(pid);
		}
	}while((pids.size() < CLIENTESPORVUELTA) && abierto);
}

// TODO a ser llamado por un timeout
void Calesita::arrancarVueltaPrematuramente(){
	darVuelta();
}

// da una vuelta e indica a todos los clientes de la calesita que la vuelta transcurrio
void Calesita::darVuelta(){
	sleep(TIEMPODEVUELTA);
	
	for (list<int>::const_iterator iterator = pids.begin(); iterator != pids.end(); ++iterator) 
		kill(*iterator,SIGNALTERMINOCALECITA);
	pids.clear();
}

// TODO a ser llamada al recibir una señal para cerrar
// por parte del administrador de la calesita
void Calesita::cerrar(){
	abierto = false;
	// TODO notificar gente en la cola
}

#endif
















