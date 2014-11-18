#ifndef CLIENT_H
#define CLIENT_H

#include "../common/Constants.h" 	// tam campos, paths de arch y letras
#include "../common/Mensaje.h"		// structs
#include "../common/Cola.h"		// cola
#include "../common/ColaResponses.h"	// cola de respuestas
#include <vector>			// vector de respuestas

class Cliente {

	public:
		Cliente();
		~Cliente();	
		void consultarBaseDeDatos(const std::string &nombre, const std::string &direccion, const std::string &telefono);
		void escribirEnBaseDeDatos(const std::string &nombre, const std::string &direccion, const std::string &telefono);
	private:
		Cola<request> colaRequests;
		ColaResp<respInicial,response> colaResponses;
		/**
		 * Arma un request
		 */
		request armarRequest(const std::string &nombre, const std::string &direccion, const std::string &telefono, bool leo);

		/*void imprimirRequest();
		void imprimirRspuestas();
		void imprimirRspuesta(int i);*/
};



#endif
