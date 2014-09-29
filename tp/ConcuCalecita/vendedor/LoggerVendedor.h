#ifndef LOGGERVENDEDOR_H_
#define LOGGERVENDEDOR_H_

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "../common/Constants.h" // archivoLogClientes

using namespace std;

class LoggerVendedor{
	public:
		// esctibe un mensaje en el log 
		static void log(const std::string logMsg);

		// esctibe un mensaje en el log indicando que el
		// vendedor esta atendiendo al cliente	
		static void logAtendiendoA(int pid);

		// esctibe un mensaje en el log indicando que el
		// vendedor esta cerrando las puertas		
		static void logCerrando();
};

// esctibe un mensaje en el log
void LoggerVendedor :: log(const string logMsg){
	if(!logMsg.empty()){
		ofstream myfile;
		myfile.open (ARCHIVOLOGVENDEDOR, ios::out | ios::app);
		myfile << logMsg;
		myfile.close();
	}
}

// esctibe un mensaje en el log indicando que el
// vendedor esta atendiendo al cliente		
void LoggerVendedor :: logAtendiendoA(int pid){
	std::ostringstream stream;
	stream << "atendiendo al cliente " << pid << "." << endl;
	LoggerVendedor::log(stream.str());
}

// esctibe un mensaje en el log indicando que el
// vendedor esta cerrando las puertas		
void LoggerVendedor :: logCerrando(){
	std::ostringstream stream;
	stream << "cerrando las persianas. " << endl;
	LoggerVendedor::log(stream.str());
}

#endif





















