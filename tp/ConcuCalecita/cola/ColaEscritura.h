#ifndef COLAESCRITURA_H
#define COLAESCRITURA_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

class ColaEscritura{

	public:
		// constructor
		ColaEscritura(const char* path);	

		// destructor
		~ColaEscritura();	

		// agrega un elemento a la cola
		void push(int data) const;

	private:
		std::string nombre;
		int fd;

};

// constructor
ColaEscritura::ColaEscritura(const char* path){
	mknod(path,S_IFIFO|0666,0);
	fd = open(path,O_WRONLY);
}

// destructor
ColaEscritura::~ColaEscritura(){
	close(fd);
	fd = -1;
}

// agrega un elemento a la cola
void ColaEscritura::push(int data) const{
	write(fd,(void*)(&data),sizeof(int));
}

#endif

















