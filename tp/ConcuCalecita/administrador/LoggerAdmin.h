#ifndef LOGGERADMIN_H_
#define LOGGERADMIN_H_

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "../common/Constants.h" // archivoLogClientes

using namespace std;

class LoggerAdmin{
	public:
		// esctibe un mensaje en el log 
		static void log(const std::string logMsg);

		// esctibe un mensaje en el log indicando que el
		// administrador cosulto la caja	
		static void logCaja(int caja);

		// esctibe un mensaje en el log indicando que el
		// administrador dio la orden de empezar a cerrar las puertas		
		static void logCerrar();

};

// esctibe un mensaje en el log
void LoggerAdmin :: log(const string logMsg){
	if(!logMsg.empty()){
		ofstream myfile;
		myfile.open (ARCHIVOLOGADMIN, ios::out | ios::app);
		myfile << logMsg;
		myfile.close();
	}
}

// esctibe un mensaje en el log indicando que el
// administrador cosulto la caja
void LoggerAdmin :: logCaja(int caja){
	std::ostringstream stream;
	stream << "el administrador consulto la caja, habían: " << caja << "$." << endl;
	LoggerAdmin::log(stream.str());
}

// esctibe un mensaje en el log indicando que el
// administrador dio la orden de empezar a cerrar las puertas		
void LoggerAdmin :: logCerrar(){
	std::ostringstream stream;
	stream << "el administrador dio la orden de cerrar la calecita." << endl;
	LoggerAdmin::log(stream.str());
}


#endif






















