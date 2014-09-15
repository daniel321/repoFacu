#include<iostream>

#include <sys/ipc.h> // shm.*
#include <sys/shm.h>

#include <sys/types.h> // waitpid
#include <sys/wait.h>

#include <unistd.h> // fork

#include <errno.h>   // def de errores
#include <stdio.h>
#include <string.h>

#include <stdlib.h>

// comandos 
// ipcs  --> muestra estado
// ipcrm --> elimina recursos
// -exit() no llama al destructor


// int flag = 0x666;

// clave --> todos los procesos necesitan la misma
// tam   --> tamaño
// flags --> 0X666 lectura y escritura para todos / IPC_CREAT / IPC_EXCL  
// int id = shmget(ftok(path,projId),sizeof(int),flag);
	
// id,addr,flags
// shmat(id,&data,flag);	

// shmdt();
// shmstcl(id,,);

using namespace std;
// maximo de mem compartida 33554432

int main(){
	const char* path = "main.cpp";
	int projId = 1;
	key_t key = ftok(path,projId);

	cout << key << endl;
 	int id = shmget(key,sizeof(int),IPC_CREAT | 0666);
	cout << "id: " << id << endl;
	cout << "err id: " << strerror(errno) << endl;

	int p =system("ipcs");
	p=p;

	int pid = fork();
	if(pid == 0){
		int* data = (int*) shmat(id,NULL,0);	
		cout << "err: " << strerror(errno) << endl;
		(*data) = 450;
		shmdt(data);
	}else{
		int* data = (int*) shmat(id,NULL,0);	
		waitpid(pid,NULL,0);
		cout << "numerito: " << *data << endl;
		shmdt(data);
		shmctl(id,IPC_RMID,NULL);
	}
	return 0;
}






































