#ifndef VENDEDOR_H
#define VENDEDOR_H

#include "../common/fifos/FifoLectura.h"
#include "../common/fifos/FifoEscritura.h"
#include "../common/logger/Logger.h"
#include "../common/SigCerrable.h"

class Vendedor : public SigCerrable
{

	public:
		Vendedor(int precioBoleto);
		~Vendedor();	
		/**
		 * atiende a los clientes en orden de llegada
		 */
		void atenderClientes();
	private:
		FifoLectura colaParaComprarBoleto;
		FifoEscritura antiEof; // Para mantener el extremo del fifo abierto
		int precioBoleto;
		Common::Logger log;

		// incrementa la caja en "precio"
		int incrementarCaja();

		// atiende a un cliente
		// envia una señal al cliente para iniciar la interacción
		// luego recibe el dinero por parte de éste, de ser suficiente, le retorna el vuelto
		// si no, le retorna el total
		void atenderCliente(int pid);
};

#endif
















