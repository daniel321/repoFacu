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
		do
		{
			colaRequests.leer(0,&req);
			if(req.leo)
			{
				int pid = req.mtype;
				std::vector<Registro> matches = bd.buscar(Registro(req.reg));
				enviarRespuestas(matches,pid);
			}
			else
			{
				bd.guardar(Registro(req.reg));
			}
		} while(!hayQueSalir());
	}
	catch (Common::InterruptException &e)
	{
	}
}

void Servidor::enviarRespuestas(std::vector<Registro> &matches, int pid)
{
	colaResponses.escribir( armarCantDeMatches(matches.size(),pid) );
	for(int i=0; i < matches.size() ; ++i)
	{
		colaResponses.escribir( armarResponse(matches[i], pid) );
	}
}

#include <cstring>
response Servidor::armarResponse(Registro &reg,long pid)
{
	response resp;
	resp.reg = reg.getRegistro();
	resp.mtype = pid;
	return resp;
}

respInicial Servidor::armarCantDeMatches(int cantMatches, long pid)
{
	respInicial resp;
	resp.mtype = pid;
	resp.matches = cantMatches;
	return resp;
}







