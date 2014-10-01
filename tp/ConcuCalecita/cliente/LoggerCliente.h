#ifndef LOGGERCLIENTE_H_
#define LOGGERCLIENTE_H_

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "../common/Constants.h" // archivoLogClientes

using namespace std;

class LoggerCliente{
	public:
		// esctibe un mensaje en el log 
		static void log(const std::string logMsg);

		// esctibe un mensaje en el log indicando que el
		// cliente no hizo la cola ya que compró el boleto previamente		
		static void logYaTeniaBoleto(int pid);

		// esctibe un mensaje en el log indicando que el
		// cliente esta haciendo la cola para comprar el boleto		
		static void logEsperandoParaComprarBoleto(int pid);

		// esctibe un mensaje en el log indicando que el
		// cliente no ha logrado comprar el boleto		
		static void logNoPudoComprarElBoletoFaltoCash(int pid,int faltante);

		// esctibe un mensaje en el log indicando que el
		// cliente no ha logrado comprar el boleto por que cerro la boleteria		
		static void logNoPudoComprarElBoletoCerroLaBoleteria(int pid);

		// esctibe un mensaje en el log indicando que el
		// cliente no ha logrado subirse a la calecita ya que esta cerro	
		static void logNoPudoSubirseCerroLaCalecita(int pid);
	
		// esctibe un mensaje en el log indicando que el
		// cliente ha logrado comprar el boleto		
		static void logAdquirioElBoleto(int pid,int sobrante);

		// esctibe un mensaje en el log indicando que el
		// cliente esta haciendo la cola para subirse a la calecita		
		static void logEsperandoParaSubirseALaCalecita(int pid);

		// esctibe un mensaje en el log indicando que el
		// cliente esta llendose a casa		
		static void logLlendoseACasa(int pid);

		// esctibe un mensaje en el log indicando que el
		// cliente recibio una señal del vendedor
		static void logRecibiSenalVendedor(int pid);

		// esctibe un mensaje en el log indicando que el
		// cliente recibio una señal de la calecita indicando que entro a la calecita
		static void logRecibiSenalCalecita(int pid);
};

// esctibe un mensaje en el log
void LoggerCliente :: log(const string logMsg){
	if(!logMsg.empty()){
		ofstream myfile;
		myfile.open (ARCHIVOLOGCLIENTES, ios::out | ios::app);
		myfile << logMsg;
		myfile.close();
	}
}

// esctibe un mensaje en el log indicando que el
// cliente no hizo la cola ya que compró el boleto previamente		
void LoggerCliente :: logYaTeniaBoleto(int pid){
	std::ostringstream stream;
	stream << "cliente " << pid << " no hace la cola por tener ya un boleto." << endl;
	LoggerCliente::log(stream.str());
}

// esctibe un mensaje en el log indicando que el
// cliente esta haciendo la cola para comprar el boleto		
void  LoggerCliente :: logEsperandoParaComprarBoleto(int pid){
	std::ostringstream stream;
	stream << "cliente " << pid << " haciendo la cola para comprar boleto." << endl;
	LoggerCliente::log(stream.str());
}

// esctibe un mensaje en el log indicando que el
// cliente no ha logrado comprar el boleto por que cerro la boleteria		
void LoggerCliente :: logNoPudoComprarElBoletoCerroLaBoleteria(int pid){
	std::ostringstream stream2;
	stream2 << "cliente " << pid << " no pudo comprar el boleto por que cerro la boleteria." << endl;
	LoggerCliente::log(stream2.str());
}

// esctibe un mensaje en el log indicando que el
// cliente no ha logrado comprar el boleto por falta de dinero		
void  LoggerCliente :: logNoPudoComprarElBoletoFaltoCash(int pid, int faltante){
	std::ostringstream stream2;
	stream2 << "cliente " << pid << " no pudo comprar el boleto por falta de dinero, faltaban " << faltante << " pesos." << endl;
	LoggerCliente::log(stream2.str());
}

// esctibe un mensaje en el log indicando que el
// cliente ha logrado comprar el boleto		
void LoggerCliente :: logAdquirioElBoleto(int pid,int sobrante){
	std::ostringstream stream2;
	stream2 << "cliente " << pid << " compró exitosamente el boleto, sobraron " << sobrante << " pesos." << endl;
	LoggerCliente::log(stream2.str());
}

// esctibe un mensaje en el log indicando que el
// cliente esta haciendo la cola para subirse a la calecita		
void LoggerCliente :: logEsperandoParaSubirseALaCalecita(int pid){
	std::ostringstream stream;
	stream << "cliente " << pid << " haciendo la cola para subisre a la calecita." << endl;
	LoggerCliente::log(stream.str());
}

// esctibe un mensaje en el log indicando que el
// cliente esta llendose a casa		
void LoggerCliente :: logLlendoseACasa(int pid){
	std::ostringstream stream;
	stream << "cliente " << pid << " llendose a casa." << endl;
	LoggerCliente::log(stream.str());
}

// esctibe un mensaje en el log indicando que el
// cliente recibio una señal del vendedor
void LoggerCliente :: logRecibiSenalVendedor(int pid){
	std::ostringstream stream;
	stream << "cliente " << pid << " recibio la señal del vendedor." << endl;
	LoggerCliente::log(stream.str());
}

// esctibe un mensaje en el log indicando que el
// cliente recibio una señal de la calecita indicando que entro a la calecita
void LoggerCliente :: logRecibiSenalCalecita(int pid){
	std::ostringstream stream;
	stream << "cliente " << pid << " entro en la calecita." << endl;
	LoggerCliente::log(stream.str());
}

// esctibe un mensaje en el log indicando que el
// cliente no ha logrado subirse a la calecita ya que esta cerro	
void LoggerCliente ::logNoPudoSubirseCerroLaCalecita(int pid){
	std::ostringstream stream2;
	stream2 << "cliente " << pid << " no pudo subirse ya que cerro la calecita." << endl;
	LoggerCliente::log(stream2.str());
}


#endif






















