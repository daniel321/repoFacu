#ifndef CLIENT_H
#define CLIENT_H

#include "../common/Constants.h" 	// tam campos, paths de arch y letras
#include "../common/Mensaje.h"		// structs
#include "../common/Cola.h"		// cola

class Cliente {

	public:
		Cliente();
		~Cliente();	

		void consultarBaseDeDatos(char nombre[tamNombre], char direccion[tamDir], char telefono[tamTel]);
		void escribirEnBaseDeDatos(char nombre[tamNombre], char direccion[tamDir], char telefono[tamTel]);

	private:
		response resp;
		request req;
		Cola<request> colaRequests;
		Cola<response> colaResponses;

		void armarRequest(char nombre[tamNombre], char direccion[tamDir],char telefono[tamTel],bool leo);

		void imprimirRequest();
		void imprimirRspuesta();
};



#endif
