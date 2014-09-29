#ifndef CONSTANTS_H
#define CONSTANTS_H

	#include<string>

	// TODO hacer configurable
	//static double tiempoMaxDeEsperaSinClientes = 100000;

	static int COLAVACIA = -1;

	static int TIEMPODEVUELTA = 10;
	static unsigned CLIENTESPORVUELTA = 5;

	static int ESPERA = 5;
	static int PRECIOBOLETO = 50;

	const char* ARCHBOLETERIACERRADA = "common/Constants.h";
	char CODEBOLETERIACERRADA = 'z';

	static int SIGNALCLIENTEVENDEDOR = 10;
	const char* ARCHCOMUNICACIONCLIENTEVENDEDOR = "/tmp/atendiendo";
	const char* ARCHCOMUNICACIONCLIENTEVENDEDOR2 = "/tmp/atendiendo2";

	const char* ARCHCOLACOMPRARBOLETOS = "/tmp/comprarBoletos";
	const char* ARCHCOLACSUBIRSEALACALECITA = "/tmp/subirseCalecita";

	static int SIGNALCLIENTECALECITA = 11;
	static int SIGNALTERMINOCALECITA = 12; 

	const char* ARCHIVOLOGCLIENTES = "logs/logClientes";
	const char* ARCHIVOLOGVENDEDOR = "logs/logVendedor";
	const char* ARCHIVOLOGCALECITA = "logs/logCalecita";

#endif