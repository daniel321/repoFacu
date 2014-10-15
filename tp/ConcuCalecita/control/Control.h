#ifndef CONTROL_H_
#define CONTROL_H_

#include <vector>
#include <string>

class Control
{
public:
	Control();
	virtual ~Control();
	void correr();
private:
	std::vector<int> pidsClientes;
	std::vector<int> pidsProcesos;
	void lanzarProcesos();
	void lanzarClientes();
	void esperarClientes();
	void cerrarProcesos();
	std::string intToStr(int i);
};

#endif /* CONTROL_H_ */
