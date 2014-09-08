#include <sys/mman.h>	// shm_open - shm_unlink    IMPORTANTE: linkear con -lrt
#include <sys/stat.h>	/* For mode constants */
#include <fcntl.h>      /* For O_* constants */

#include <sys/wait.h>  	// wait
#include <unistd.h>  	// fork
#include <stdlib.h>	// rand,atoi,sleep

#include <iostream>	// cout
#include <string>	// string
#include <sstream>	// stringstream
#include <fstream>	// ofstream

#define NUMPROC 10
#define DIR "seccCrit.txt"

void childCode(int id,int *turn);

void critSecc(int id);
int writeToFile(const std::string text);

using namespace std;

int main (){
	ofstream archi (DIR,ios::trunc); // trunco archivo
	archi.close();

	int fd = shm_open("int", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);	// es como un archivo mapeado a memoria, 		
	ftruncate(fd, sizeof(int));					// pero sin el archivo :p					

	int *sharedInt = (int*) mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	(*sharedInt) = 0;

	for(int i=0; i<NUMPROC; i++){
		int pid = fork();
		if(pid == 0){
			childCode(i,sharedInt);	
		}
	}

	for(int i=0; i<NUMPROC; i++){
		int retVal;			
		int id = wait(&retVal);			
	}
	return 0;
}

// manejo concurrente usando mem compartida
void childCode(int id,int *turn){
	while(id != (*turn)){
		sleep(1);
	}

	critSecc(id);

	(*turn)++;
	cout << endl << "turno: " << (*turn);	

	exit(0);
}

// seccion critica de los programitas
void critSecc(int id){	
	std::ostringstream msg;
	msg << std::string("proceso numero ") << id;
	writeToFile(msg.str());
}

// escribe la linea indicada a continuacion de la ultima linea del archivo (lo crea en caso de no existir)
// retorna 1 en caso de error o 0 si el archivo se escribe correctamente
int writeToFile(const std::string text){
	ofstream archi (DIR,ios::app);
	
	archi << text <<"\n";
  	archi.close();
  	return 0;
}


















