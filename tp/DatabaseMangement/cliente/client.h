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

		void consultarBaseDeDatos(char nombre[tamNombre], char direccion[tamDir], char telefono[tamTel]);
		void escribirEnBaseDeDatos(char nombre[tamNombre], char direccion[tamDir], char telefono[tamTel]);

	private:
		request req;
		std::vector<response> resp;
		respInicial cantidadDeMatches;

		Cola<request> colaRequests;
		ColaResp<respInicial,response> colaResponses;

		void armarRequest(char nombre[tamNombre], char direccion[tamDir],char telefono[tamTel],bool leo);

		void imprimirRequest();
		void imprimirRspuestas();
		void imprimirRspuesta(int i);
};



#endif
