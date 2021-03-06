#ifndef CLIENTSOCKET_H_
#define CLIENTSOCKET_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include "Socket.h"

class ClientSocket : public Socket {

	private:
		std::string ipServidor;

	public:
		ClientSocket ( const std::string& ipServidor,const unsigned int port );
		~ClientSocket ();

		void abrirConexion ();

		int enviar ( const void* buffer,const unsigned int buffSize ) const;
		int recibir ( void* buffer,const unsigned int buffSize ) const;

		void cerrarConexion () const;
};

#endif /* CLIENTSOCKET_H_ */
