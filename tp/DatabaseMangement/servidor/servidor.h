#ifndef SERVIDOR_H
#define SERVIDOR_H

#include "../common/Constants.h" 	// tam campos, paths de arch y letras
#include "../common/Mensaje.h"		// structs
#include "../common/Cola.h"		// cola
#include "../common/ColaResponses.h"	// cola de respuestas
#include <vector>			// vector de respuestas

class Servidor{

	public:
		Servidor();
		~Servidor();	

		void atenderClientes();
		void pararDeAtender();

	private:
		request req;
		std::vector<response> resp;
		respInicial cantidadDeMatches;

		Cola<request> colaRequests;
		ColaResp<respInicial,response> colaResponses;

		bool atendiendo;

		int leerDeLaBaseDeDatos();
		void escribirEnLaBaseDeDatos();
		
		void armarCantDeMatches(int matches,long mtype);
		void armarRespuestaDummy(long mtype);
		void armarRespuesta(char nombre[tamNombre], char direccion[tamDir], char telefono[tamTel],long mtype);

		void enviarRespuestas(int cantMatches,int pid);

		void imprimirRequest();
		void imprimirRspuestas();
		void imprimirRspuesta(int i);
};

#endif
















