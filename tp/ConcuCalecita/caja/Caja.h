#ifndef VENDEDOR_H
#define VENDEDOR_H

#include "../common/fifos/FifoLectura.h"
#include "../common/fifos/FifoEscritura.h"
#include "../common/SigCerrable.h"

class Caja : public SigCerrable{

	public:
		Caja(int cajaInicial);	
		~Caja();

		// atiende a los que necesitan cosultar o modificar la caja
		void esperarModificaciones();
	private:
		int caja;
		FifoLectura colaParaConsultarCaja;
		FifoEscritura fifoRespustaVendedor;
		FifoEscritura fifoRespuestaAdministrador;

		// incrementa la caja en un boleto vendido
		// y notifica de la nueva caja al vendedor
		void responderAVendedor(int ganancia);

		// notifica el valor de la caja al administrador
		void responderAAdmin();

};

#endif
















