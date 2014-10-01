#include<iostream>
#include "common/FifoHandler.h"

using namespace std;

int main(){
	FifoHandler::escribir("aux.txt",1);
	cout << "el valor inicial fue: " << FifoHandler::leer("aux2.txt") << endl;
	FifoHandler::escribir("aux3.txt",3);

	return 0;
}




































