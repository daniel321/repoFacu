#include "client.h"

#include <sys/types.h>					// getpid()
#include <unistd.h>
#include <sstream>

#include "../common/signals/SignalHandler.h"

#include "../common/Constants.h"
#include "../common/fifos/FifoHandler.h"
#include "../common/logger/LogStreamBufSinc.h"

const char archLog[]  = "logs/logClientes";

Cliente::Cliente(int presup,bool boleto)
	:	tengoBoleto(boleto), meCerraronLaCalesita(false), cash(presup),
	 	id(getpid()), log(new Common::LogStreamBufSinc(archLog)) {}

Cliente::~Cliente()
{
	log << "Cliente " << id << " yendose a casa." << std::endl;
}

// el cliente se agrega a si mismo a una cola y espera ser atendido
void Cliente::esperarEnLaCola(const char* pathCola,BoolHandler& handler){
	FifoHandler::escribir(pathCola,id);

	while((handler.getBandera() != 1) && !meCerraronLaCalesita)
		sleep(Espera);
}

// espera la indicacion del usuario para arrancar a atender
void Cliente::comprarBoleto(){
	if(!tengoBoleto && !meCerraronLaCalesita){
		log << "Cliente " << id << " haciendo la cola para comprar boleto." << std::endl;

		BoolHandler handler(SigClienteVendedor);
		SignalHandler::getInstance()->registrarHandler(SigClienteVendedor,&handler);

		esperarEnLaCola(ArchColaBoletos,handler);

		if(meCerraronLaCalesita){
			log << "Cliente " << id << " no pudo comprar el boleto por que cerro la boleteria." << std::endl;
		}else{
			if(handler.getBandera()){
				log << "Cliente " << id << " recibio la señal del vendedor." << std::endl;
				comunicacionConElVendedor();
			}
		}
	}else{
		log << "Cliente " << id << " no hace la cola por tener ya un boleto." << std::endl;
	}
}

// ocurre cuando es atendido (x interrupción)
// envia al vendedor el dinero disponible y recibe vuelto
// en caso que el dinero no sea suficiente, no se produce cambio algúno
// (y el cliente se va a casa...)
void Cliente::comunicacionConElVendedor(){

	FifoHandler::escribir(ARCHCOMUNICACIONCLIENTEVENDEDOR,cash);
	int sobrante = FifoHandler::leer(ARCHCOMUNICACIONCLIENTEVENDEDOR2);

	if (sobrante != cash){
		log << "Cliente " << id << " compró exitosamente el boleto, sobraron " << sobrante << " pesos." << std::endl;
		tengoBoleto = true;
	}else{
		log << "cliente " << id << " no pudo comprar el boleto por falta de dinero, faltaban "
				<< PrecioBoleto-cash << " pesos." << std::endl;
	}

	cash = sobrante;
}

// espera a poder subirse en la calesita
void Cliente::subirseALaCalesita(){
	if(meCerraronLaCalesita){
		log << "Cliente " << id << " no pudo subirse ya que cerro la calesita." << std::endl;
	}else{
		if(tengoBoleto){
			log << "cliente " << id << " haciendo la cola para subisre a la calesita." << std::endl;

			BoolHandler handler(SigClienteCalesita);
			SignalHandler::getInstance()->registrarHandler(SigClienteCalesita,&handler);

			esperarEnLaCola(ArchColaCalesita,handler);

			if(handler.getBandera() && !meCerraronLaCalesita){
				log << "Cliente " << id << " entro en la calesita." << std::endl;
				subidaALaCalesita();
				log << "Cliente " << id << " salio de la calesita." << std::endl;
			}
		}
	}
}

// ocurre cuando se sube a la calecita (x interrupción)
void Cliente::subidaALaCalesita(){
	tengoBoleto = false;

	BoolHandler handler(SigTerminoCalesita);
	SignalHandler::getInstance()->registrarHandler(SigTerminoCalesita,&handler);

	while(handler.getBandera() != 1)
		sleep(Espera);
}

// TODO a ser llamada al recibir una señal indicando que cerro la calecita
void Cliente::echar(){
	meCerraronLaCalesita = true;
}
