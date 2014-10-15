#include "calesita.h"

#include <ctime>					// clock
#include <signal.h>					// kill
#include "../common/Constants.h" 			// archivo,code
#include "../common/fifos/FifoHandler.h"
#include "../common/logger/LogStreamBuf.h"
#include "../common/signals/SignalHandler.h"
#include "../common/signals/VoidHandler.h"
#include "../common/exception/ErrnoWrap.h"
#include "../common/exception/InterruptException.h"

const char archLog[] = "logs/logCalesita";

int Calesita::TiempoDeVuelta = 5;

Calesita::Calesita(int numeroAsientos) : colaParaEntrar(ArchColaCalesita), abierto(true),
		log(new Common::LogStreamBuf(archLog)), asientos(numeroAsientos), numeroAsientos(numeroAsientos)
{
	SignalHandler::getInstance()->registrarHandler(SIGALRM, new VoidHandler());
	int interrupt = siginterrupt(SIGALRM, 1);
	if (interrupt == -1) throw Common::ErrnoWrap();
	log << "Abriendo la calesita." << endl;
	colaParaEntrar.abrir();
}

Calesita::~Calesita(){
	log << "Calesita cerrando." << endl;
	asientos.liberar();
}

void Calesita::operar(){
	do{
		log << "Calesita esperando que llegue mas gente." << endl;
		if (abierto) esperarClientes();
		log << "Calesita dando una vuelta con " << pids.size() << " pasajeros." << endl;
		darVuelta();
		log << "Calesita termino de dar la vuelta." << endl;
	} while(abierto || pids.size() > 0);

}

void Calesita::esperarClientes()
{
	bool timeOut = false;
	int pid = 0;
	do{
		timeOut = false;
		pid = 0;
		alarm(TimeoutCalesita);
		try
		{
			pid = FifoHandler::leer(colaParaEntrar);
			if(pid != 0)
			{
				kill(pid,SigClienteCalesita);
				pids.push_back(pid);
			}
		}
		catch (Common::InterruptException &e)
		{
			log << "Timeout de la calesita. Hay " << pids.size() << " niños arriba." << std::endl;
			if (pids.size() > 0) timeOut = true;
		}
		alarm(0);
	} while( (pids.size() < numeroAsientos) && !timeOut && abierto);
}

void Calesita::darVuelta(){
	sleep(TiempoDeVuelta);

	for (list<int>::const_iterator iterator = pids.begin(); iterator != pids.end(); ++iterator)
		kill(*iterator,SigTerminoCalesita);
	pids.clear();
	asientos.reset();
}

// TODO a ser llamada al recibir una señal para cerrar
// por parte del administrador de la calesita
void Calesita::cerrar(){
	abierto = false;
	// TODO notificar gente en la cola
}

