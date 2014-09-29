#ifndef LOGGERCALECITA_H_
#define LOGGERCALECITA_H_

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "../common/Constants.h" // archivoLogClientes

using namespace std;

class LoggerCalecita{
	public:
		// esctibe un mensaje en el log 
		static void log(const std::string logMsg);

		// esctibe un mensaje en el log indicando que la
		// calecita esta esperando que llege mas gente		
		static void logEsperandoGente();

		// esctibe un mensaje en el log indicando que la 
		// calecita esta dando una vuelta	
		static void logDandoUnaVuelta(int cantidad);

		// esctibe un mensaje en el log indicando que la 
		// calecita termino de dar la vuelta	
		static void logVueltaFinalizada();

		// esctibe un mensaje en el log indicando que la
		// calecita esta cerrando		
		static void logCerrando();
};

// esctibe un mensaje en el log
void LoggerCalecita :: log(const string logMsg){
	if(!logMsg.empty()){
		ofstream myfile;
		myfile.open (ARCHIVOLOGCALECITA, ios::out | ios::app);
		myfile << logMsg;
		myfile.close();
	}
}

// esctibe un mensaje en el log indicando que la
// calecita esta esperando que llege mas gente		
void LoggerCalecita :: logEsperandoGente(){	
	std::ostringstream stream;
	stream << "calecita esperando que llegue mas gente." << endl;
	LoggerCalecita::log(stream.str());
}

// esctibe un mensaje en el log indicando que la 
// calecita esta dando una vuelta	
void LoggerCalecita :: logDandoUnaVuelta(int cantidad){
	std::ostringstream stream;
	stream << "calecita dando una vuelta con " << cantidad << " pasajeros." << endl;
	LoggerCalecita::log(stream.str());
}

// esctibe un mensaje en el log indicando que la 
// calecita termino de dar la vuelta	
void LoggerCalecita :: logVueltaFinalizada(){
	std::ostringstream stream;
	stream << "calecita termino de dar la vuelta." << endl;
	LoggerCalecita::log(stream.str());
}

// esctibe un mensaje en el log indicando que la
// calecita esta cerrando		
void LoggerCalecita :: logCerrando(){
	std::ostringstream stream;
	stream << "calecita cerrando." << endl;
	LoggerCalecita::log(stream.str());
}

#endif





















