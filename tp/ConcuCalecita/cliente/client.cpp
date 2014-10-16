#include "client.h"

#include <sys/types.h>					// getpid()
#include <unistd.h>
#include <sstream>

#include "../common/signals/SignalHandler.h"

#include "../common/Constants.h"
#include "../common/fifos/FifoHandler.h"
#include "../common/logger/LogStreamBufSinc.h"
#include "../common/Asientos.h"

const char archLog[]  = "logs/logClientes";

Cliente::Cliente(int presup,bool boleto)
	:	tengoBoleto(boleto), meCerraronLaCalesita(false), cash(presup),
	 	id(getpid()), log(new Common::LogStreamBufSinc(archLog))
{
	SignalHandler::bloquearSenial(SigClienteCalesita);
	SignalHandler::bloquearSenial(SigClienteVendedor);
	SignalHandler::bloquearSenial(SigTerminoCalesita);
}

Cliente::~Cliente()
{
	log << "Cliente " << id << " yendose a casa." << std::endl;
}

// el cliente se agrega a si mismo a una cola y espera ser atendido
void Cliente::esperarEnLaCola(const char* pathCola, int signum)
{
	FifoHandler::escribir(pathCola,id);
	SignalHandler::esperarSenial(signum);
}

// espera la indicacion del usuario para arrancar a atender
void Cliente::comprarBoleto(){
	if(!tengoBoleto && !meCerraronLaCalesita)
	{
		log << "Cliente " << id << " haciendo la cola para comprar boleto." << std::endl;

		esperarEnLaCola(ArchColaBoletos,SigClienteVendedor);

		if(meCerraronLaCalesita)
		{
			log << "Cliente " << id << " no pudo comprar el boleto por que cerro la boleteria." << std::endl;
		}
		else
		{
			log << "Cliente " << id << " recibio la señal del vendedor." << std::endl;
			comunicacionConElVendedor();
		}
	}
	else
	{
		log << "Cliente " << id << " no hace la cola por tener ya un boleto." << std::endl;
	}
}

// ocurre cuando es atendido (x interrupción)
// envia al vendedor el dinero disponible y recibe vuelto
// en caso que el dinero no sea suficiente, no se produce cambio algúno
// (y el cliente se va a casa...)
void Cliente::comunicacionConElVendedor(){

	FifoHandler::escribir(ARCHCOMUNICACIONCLIENTEVENDEDOR,cash);
	int sobrante = FifoHandler::leer(ARCHCOMUNICACIONCLIENTEVENDEDOR2, true);

	if (sobrante != cash){
		log << "Cliente " << id << " compró exitosamente el boleto, sobraron " << sobrante << " pesos." << std::endl;
		tengoBoleto = true;
	}else{
		log << "cliente " << id << " no pudo comprar el boleto por falta de dinero, tenía:" << cash << std::endl;
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

			esperarEnLaCola(ArchColaCalesita,SigClienteCalesita);

			if(!meCerraronLaCalesita)
			{
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
	Asientos().sentarse(id, &log);
	SignalHandler::esperarSenial(SigTerminoCalesita);
}

// TODO a ser llamada al recibir una señal indicando que cerro la calecita
void Cliente::echar(){
	meCerraronLaCalesita = true;
}
