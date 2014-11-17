#ifndef SERVIDOR_H
#define SERVIDOR_H

#include "../common/Constants.h" 	// tam campos, paths de arch y letras
#include "../common/Mensaje.h"		// structs
#include "../common/Cola.h"		// cola

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
		Cola<request> colaRequests;
		Cola<response> colaResponses;
		BaseDeDatos bd;
		
		void armarRespuestaDummy(long mtype);
		void armarRespuesta(char nombre[tamNombre], char direccion[tamDir], char telefono[tamTel],long mtype);

		void imprimirRequest(request &req);
		void imprimirRspuesta(response &resp);
};

#endif
















