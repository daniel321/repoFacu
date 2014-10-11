#ifdef EJEMPLO_3

#include <iostream>
#include "LockFile.h"

using namespace std;

int main () {

	static const std::string NOMBRE_ARCHIVO = "salida.txt";
	static const std::string TEXTO_HIJO = "Mensaje del hijo\n";
	static const std::string TEXTO_PADRE = "Mensaje del padre\n";

	pid_t pid = fork ();

	if ( pid == 0 ) {

		LockFile lock ( NOMBRE_ARCHIVO );
		lock.tomarLock ();

		lock.escribir ( static_cast<const void*>(TEXTO_HIJO.c_str()),TEXTO_HIJO.size() );
		sleep ( 1 );
		lock.escribir ( static_cast<const void*>(TEXTO_HIJO.c_str()),TEXTO_HIJO.size() );
		lock.escribir ( static_cast<const void*>(TEXTO_HIJO.c_str()),TEXTO_HIJO.size() );

		lock.liberarLock ();
		cout << "Hijo: fin del programa" << endl;
		return 0;

	} else {

		LockFile lock ( NOMBRE_ARCHIVO );
		lock.tomarLock ();

		lock.escribir ( static_cast<const void*>(TEXTO_PADRE.c_str()),TEXTO_PADRE.size() );
		lock.escribir ( static_cast<const void*>(TEXTO_PADRE.c_str()),TEXTO_PADRE.size() );
		sleep ( 1 );
		lock.escribir ( static_cast<const void*>(TEXTO_PADRE.c_str()),TEXTO_PADRE.size() );

		lock.liberarLock ();
		cout << "Padre: fin del programa" << endl;
		return 0;

	}

}

#endif
