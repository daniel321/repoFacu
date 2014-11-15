#include <iostream>
#include "Sockets/ServerSocket.h"


int main () {

	static const unsigned int BUFFSIZE = 255;
	static const unsigned int SERVER_PORT = 16000;

	try {
		ServerSocket socket ( SERVER_PORT );
		char buffer[BUFFSIZE];

		std::cout << "EchoServer: esperando conexiones" << std::endl;
		std::cout << "EchoServer: enviar la cadena 's' desde el cliente para terminar" << std::endl << std::endl;
		socket.abrirConexion();

		std::string peticion;

		do {
			int bytesRecibidos = socket.recibir ( static_cast<void*>(buffer),BUFFSIZE );
			peticion = buffer;
			peticion.resize(bytesRecibidos);
			std::cout << "EchoServer: dato recibido: " << peticion << std::endl;

			std::cout << "EchoServer: enviando respuesta . . ." << std::endl;
			socket.enviar ( static_cast<const void*>(peticion.c_str()),peticion.size() );
		} while ( peticion != std::string("s") );

		std::cout << "EchoServer: cerrando conexion" << std::endl;
		socket.cerrarConexion ();

	} catch ( std::string& mensaje ) {
		std::cout << mensaje << std::endl;
	}

	return 0;
}

