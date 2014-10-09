#ifndef VENDEDOR_H
#define VENDEDOR_H

#include "../common/fifos/FifoLectura.h"

class Caja {

	public:
		Caja(int cajaInicial);	

		// atiende a los que necesitan cosultar o modificar la caja
		void esperarModificaciones();

		// TODO a ser llamada al recibir una señal para cerrar
		// por parte del administrador de la calecita
		void cerrar();

	private:
		int caja;
		FifoLectura colaParaConsultarCaja;
		bool abierto;

		// incrementa la caja en un boleto vendido
		// y notifica de la nueva caja al vendedor
		void responderAVendedor();

		// notifica el valor de la caja al administrador
		void responderAAdmin();

};

#endif
















