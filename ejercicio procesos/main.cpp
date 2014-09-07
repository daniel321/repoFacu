#include <sys/types.h>
#include <sys/wait.h>  	// wait
#include <unistd.h>  	// fork
#include <stdlib.h>	// rand,atoi
#include <time.h> 	// srand
#include <iostream>	// cout

using namespace std;

void childCode();
int randomNumber(int max,int offset);
void displayResults(int numProc);

int main (int argc, char* argv[]){
	if(argc < 2)
		return 1;

	int numProc = atoi(argv[1]);
	for(int i=0; i<numProc; i++){
		int pid = fork();
		if(pid == 0){
			childCode();	
		}
	}

	displayResults(numProc);	
	return 0;
}

void childCode(){
	int amount = randomNumber(10,0);

	cout << "\nsoy: " << getpid() << " duermo: " << amount << endl;
	sleep(amount);
	_Exit(amount);	
}

void displayResults(int numProc){
	int retval = system("ps");
	retval = retval;

	for(int i=0; i<numProc; i++){
		int retVal;			// importante, el valor de status contiene mas info que solo el val de retorno
		int id = wait(&retVal);		// usar macros del manual para obtener la info (incluido el valor de retorno)
		cout << "\nel proceso: " << id << " durmió: " << WEXITSTATUS(retVal) << endl; // ej: WEXITSTATUS
	}
	cout << endl;
}

int randomNumber(int max,int offset){
	srand(time(NULL)*getpid());
	return ((rand()%max)+offset);
}

































