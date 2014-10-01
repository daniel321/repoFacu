#include<iostream>
#include "common/FifoHandler.h"

using namespace std;

int main(){
	cout << "el valor inicial fue: " << FifoHandler::leer("aux.txt") << endl;
	FifoHandler::escribir("aux2.txt",2);
	cout << "el valor final fue: " << FifoHandler::leer("aux3.txt") << endl;
	return 0;
}






















