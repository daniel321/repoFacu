#include "calesita.h"

#include <ctime>					// clock
#include <signal.h>					// kill
#include "../common/Constants.h" 			// archivo,code
#include "../common/fifos/FifoHandler.h"
#include "../common/logger/LogStreamBuf.h"
#include "../common/signals/SignalHandler.h"
#include "../common/exception/ErrnoWrap.h"
#include "../common/exception/InterruptException.h"

const char archLog[] = "logs/logCalesita";

Calesita::Calesita(int numeroAsientos, int tiempoVuelta) : colaParaEntrar(ArchColaCalesita), antiEof(ArchColaCalesita),
		log(new Common::LogStreamBuf(archLog)), asientos(numeroAsientos),
		numeroAsientos(numeroAsientos), tiempoVuelta(tiempoVuelta)
{
	SignalHandler::getInstance()->registrarHandler(SIGALRM, &alarmHandler);
	int interrupt = siginterrupt(SIGALRM, 1);
	if (interrupt == -1) throw Common::ErrnoWrap();
	SignalHandler::getInstance()->registrarHandler(SigQuit, &quitHandler);
	interrupt = siginterrupt(SigQuit, 1);
	if (interrupt == -1) throw Common::ErrnoWrap();
	log << "Abriendo la calesita." << endl;
	try
	{
		colaParaEntrar.abrir();
		antiEof.abrir();
	}
	catch (Common::InterruptException &e)
	{

	}
}

Calesita::~Calesita(){
	log << "Calesita cerrando." << endl;
	asientos.liberar();
	SignalHandler::getInstance()->destruir();
	colaParaEntrar.cerrar();
	antiEof.cerrar();
	colaParaEntrar.eliminar();
}

void Calesita::operar(){
	do{
		log << "Calesita esperando que llegue mas gente." << endl;
		if (!quitHandler.getBandera()) esperarClientes();
		if (pids.size() > 0)
		{
			log << "Calesita dando una vuelta con " << pids.size() << " pasajeros." << endl;
			darVuelta();
			log << "Calesita termino de dar la vuelta." << endl;
		}
	} while(!quitHandler.getBandera() || pids.size() > 0);

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
	} while( (pids.size() < numeroAsientos) && !timeOut && !quitHandler.getBandera());
}

void Calesita::darVuelta(){
	sleep(tiempoVuelta);

	for (list<int>::const_iterator iterator = pids.begin(); iterator != pids.end(); ++iterator)
		kill(*iterator,SigTerminoCalesita);
	pids.clear();
	asientos.reset();
}
