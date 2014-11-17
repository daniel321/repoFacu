#include "servidor.h"

#include <iostream>			// std::cout
#include <string.h>			// strncpy

const std::string BDArch("bd.tp2");

Servidor::Servidor() : colaRequests(ARCHI_COLA_REQUESTS,LETRA_REQUESTS)
	,colaResponses(ARCHI_COLA_RESPONSES,LETRA_RESPONSES), bd(BDArch)
{
}

Servidor::~Servidor()
{
	colaRequests.destruir();
	colaResponses.destruir();
}

void Servidor::atenderClientes()
{
	try
	{
		request req;
		do{
			int cantLeidos = colaRequests.leer(0,&req);
			if(cantLeidos > 0){
				imprimirRequest(req);

				if(req.leo)
				{
					std::vector<Registro> = bd.buscar(Registro(req.reg));
					// TODO
				}
				else
				{
					bd.guardar(Registro(req.reg));
				}
			}
		}while(!hayQueSalir());
	}
	catch (Common::InterruptException &e)
	{
	}
}

/*
void Servidor::armarRespuesta(char nombre[tamNombre], char direccion[tamDir], char telefono[tamTel],long mtype){
	strncpy(resp.nombre, nombre, tamNombre);
	strncpy(resp.direccion, direccion, tamDir);
	strncpy(resp.telefono, telefono, tamTel);
	resp.mtype = mtype;
}

void Servidor::armarRespuestaDummy(long mtype){
	strncpy(resp.nombre, NOMBRE_DUMMY, tamNombre);
	strncpy(resp.direccion, DIR_DUMMY, tamDir);
	strncpy(resp.telefono, TEL_DUMMY, tamTel);
	resp.mtype = mtype;
}*/

void Servidor::imprimirRequest(request &req){
	std::cout << std::endl;
	std::cout << "Request recibida por el server: " << std::endl;
	std::cout << "Nombre: " << req.reg.nombre << std::endl;
	std::cout << "Direccion: " << req.reg.direccion << std::endl;
	std::cout << "Telefono: " << req.reg.telefono << std::endl;
	std::cout << "Lectura: " << req.leo << std::endl;
	std::cout << "Tipo: " << req.mtype << std::endl << std::endl;
}


void Servidor::imprimirRspuesta(response &resp){
	std::cout << std::endl;
	std::cout << "Respuesta enviada por el server: " << std::endl;
	std::cout << "Nombre: " << resp.reg.nombre << std::endl;
	std::cout << "Direccion: " << resp.reg.direccion << std::endl;
	std::cout << "Telefono: " << resp.reg.telefono << std::endl;
	std::cout << "Tipo: " << resp.mtype << std::endl << std::endl;
}







