#ifndef SERVIDOR_H
#define SERVIDOR_H

#include "../common/Constants.h" 	// tam campos, paths de arch y letras
#include "../common/Mensaje.h"		// structs
#include "../common/Cola.h"		// cola
#include "../common/ColaResponses.h"	// cola de respuestas
#include <vector>			// vector de respuestas

#include "../common/Registro.h"
#include "../common/SigCerrable.h"
#include "BaseDeDatos.h"

class Servidor : public SigCerrable
{
	public:
		Servidor();
		~Servidor();	

		void atenderClientes();
		void pararDeAtender();

	private:
		BaseDeDatos bd;
		std::vector<response> resp;

		Cola<request> colaRequests;
		ColaResp<respInicial,response> colaResponses;
		
		/**
		 * Arma una respuesta inicial con la cantidad de matches y el pid al cual se mandara
		 */
		respInicial armarCantDeMatches(int cantMatches,long pid);
		/**
		 * Arma una respuesta en base a un registro a enviar
		 */
		response armarResponse(Registro &reg,long pid);
		/**
		 * Envia respuestas
		 */
		void enviarRespuestas(std::vector<Registro> &matches, int pid);

};

#endif
















