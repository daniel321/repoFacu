#ifndef SERVIDOR_H
#define SERVIDOR_H

#include "../common/Constants.h" 	// tam campos, paths de arch y letras
#include "../common/Mensaje.h"		// structs
#include "../common/Cola.h"		// cola

class Servidor{

	public:
		Servidor();
		~Servidor();	

		void atenderClientes();
		void pararDeAtender();

	private:
		request req;
		response resp;
		Cola<request> colaRequests;
		Cola<response> colaResponses;

		bool atendiendo;

		bool leerDeLaBaseDeDatos();
		void escribirEnLaBaseDeDatos();
		
		void armarRespuestaDummy(long mtype);
		void armarRespuesta(char nombre[tamNombre], char direccion[tamDir], char telefono[tamTel],long mtype);

		void imprimirRequest();
		void imprimirRspuesta();
};

#endif
















