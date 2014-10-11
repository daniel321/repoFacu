#ifdef EJEMPLO_2

#include <iostream>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

using namespace std;

int main () {

	static const std::string NOMBRE_ARCHIVO = "salida.txt";
	static const std::string TEXTO_HIJO = "Mensaje del hijo\n";
	static const std::string TEXTO_PADRE = "Mensaje del padre\n";

	pid_t pid = fork ();

	if ( pid == 0 ) {

		int descriptor = open ( NOMBRE_ARCHIVO.c_str(),O_CREAT | O_WRONLY,0777 );

		if ( descriptor > 0 ) {
			lseek ( descriptor,0,SEEK_END );
			write ( descriptor,static_cast<const void*>(TEXTO_HIJO.c_str()),TEXTO_HIJO.size() );
			sleep ( 1 );

			lseek ( descriptor,0,SEEK_END );
			write ( descriptor,static_cast<const void*>(TEXTO_HIJO.c_str()),TEXTO_HIJO.size() );

			lseek ( descriptor,0,SEEK_END );
			write ( descriptor,static_cast<const void*>(TEXTO_HIJO.c_str()),TEXTO_HIJO.size() );

			close ( descriptor );
		} else {
			perror ( "Hijo: error al abrir archivo" );
		}

		cout << "Hijo: fin del programa" << endl;
		return 0;

	} else {

		int descriptor = open ( NOMBRE_ARCHIVO.c_str(),O_CREAT | O_WRONLY,0777 );

		if ( descriptor > 0 ) {
			lseek ( descriptor,0,SEEK_END );
			write ( descriptor,static_cast<const void*>(TEXTO_PADRE.c_str()),TEXTO_PADRE.size() );

			lseek ( descriptor,0,SEEK_END );
			write ( descriptor,static_cast<const void*>(TEXTO_PADRE.c_str()),TEXTO_PADRE.size() );
			sleep ( 1 );

			lseek ( descriptor,0,SEEK_END );
			write ( descriptor,static_cast<const void*>(TEXTO_PADRE.c_str()),TEXTO_PADRE.size() );

			close ( descriptor );
		} else {
			perror ( "Padre: error al abrir archivo" );
		}

		cout << "Padre: fin del programa" << endl;
		return 0;

	}

}

#endif
