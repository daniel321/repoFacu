#include "admin.h" 	// Administrador
#include <iostream>

using namespace std;

int main (int argc, char** argv) {

	Administrador admin;
	admin.consultarCaja();

	cout << "cierro? (s/n)" << endl;
	char sn;
	cin >> sn;

	if(sn)
		admin.CerrarCalecita();

	return 0;
}


















