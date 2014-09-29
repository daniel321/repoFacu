#ifndef COLALECTURA_H
#define COLALECTURA_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

using namespace std;

class ColaLectura{

	public:
		// constructor
		ColaLectura(const char* path);	

		// destructor
		~ColaLectura();	

		// retorna el primer elemento de la cola
		int pop() const;

	private:
		std::string nombre;
		int fd;

};

// constructor
ColaLectura::ColaLectura(const char* path){
	mknod(path,S_IFIFO|0666,0);
	
	FILE* f = fopen(path, "w");
	fclose(f);

	fd = open(path,O_RDONLY | O_TRUNC);
}

// destructor
ColaLectura::~ColaLectura(){
	unlink(nombre.c_str());
	close(fd);
	fd = -1;
}

// retorna el primer elemento de la cola
int ColaLectura::pop() const{
	int valor;
	read(fd,(void*)(&valor),sizeof(int));

	if(valor != EOF)
		return valor;
	else
		return COLAVACIA;
}

#endif

















