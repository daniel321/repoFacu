#ifndef CLIENT_H
#define CLIENT_H

#include "../common/logger/Logger.h"
#include "../common/signals/BoolHandler.h"

class Cliente {

	public:
		Cliente(int presup,bool boleto);	
		~Cliente();	

		// espera a ser atendido y compra el boleto	
		void comprarBoleto();

		// ocurre cuando es atendido (x interrupción)
		// envia al vendedor el dinero disponible y recibe vuelto
		// en caso que el dinero no sea suficiente, no se produce cambio algúno
		// (y el cliente se va a casa...)
		void comunicacionConElVendedor();

		// espera a poder subirse en la calecita
		void subirseALaCalesita();

		// ocurre cuando se sube a la calecita (x interrupción)
		void subidaALaCalesita();

		// TODO a ser llamada al recibir una señal indicando que cerro la calecita
		void echar();

	private:
		bool tengoBoleto;
		bool meCerraronLaCalesita;
		int  cash;
		int  id;
		Common::Logger log;

		// el cliente se agrega a si mismo a una cola y espera ser atendido
		void esperarEnLaCola(const char* pathCola,BoolHandler& handler);
};

#endif
