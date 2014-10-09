#include "calesita.h"

#include <ctime>					// clock
#include <signal.h>					// kill
#include "../common/Constants.h" 			// archivo,code
#include "../common/fifos/FifoHandler.h"
#include "../common/logger/LogStreamBuf.h"

const char archLog[] = "logs/logCalesita";

Calesita::Calesita() : colaParaEntrar(ARCHCOLACSUBIRSEALACALECITA), abierto(true), log(new Common::LogStreamBuf(archLog))
{
	colaParaEntrar.abrir();
}

Calesita::~Calesita(){
	log << "Calesita cerrando." << endl;
}

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

