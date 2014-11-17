#ifndef CLIENT_H
#define CLIENT_H

#include "../common/Constants.h" 	// tam campos, paths de arch y letras
#include "../common/Mensaje.h"		// structs
#include "../common/Cola.h"		// cola

class Cliente {

	public:
		Cliente();
		~Cliente();	
		void consultarBaseDeDatos(const std::string &nombre, const std::string &direccion, const std::string &telefono);
		void escribirEnBaseDeDatos(const std::string &nombre, const std::string &direccion, const std::string &telefono);
	private:
		response resp;
		request req;
		Cola<request> colaRequests;
		Cola<response> colaResponses;
		void armarRequest(const std::string &nombre, const std::string &direccion, const std::string &telefono, bool leo);
		void imprimirRequest();
		void imprimirRspuesta();
};



#endif
