#include "LogStreamBuf.h"

#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <iostream>

namespace Common
{

LogStreamBuf::LogStreamBuf(const char* path) : fileDescriptor(0)
{
	fileDescriptor = ::open(path, O_WRONLY | O_APPEND | O_CREAT, S_IRWXU);
	if (fileDescriptor == -1)
	{
		throw std::ios_base::failure(strerror(errno));
	}
}

LogStreamBuf::~LogStreamBuf()
{
	close(fileDescriptor);
}

std::string LogStreamBuf::timestamp()
{
	time_t fecha = time(0);
	std::string strFecha(asctime(localtime(&fecha)));
	strFecha.erase(strFecha.length()-1, 1); // Borramos el \n
	return strFecha;
}

int LogStreamBuf::sync ()
{
	std::cout << "flushed" << std::endl;
	std::string linea("["+timestamp()+"] "+str());
	ssize_t retorno = 0;
	ssize_t largoInicial = linea.length();
	ssize_t faltaEscribir = linea.length();
	while (faltaEscribir > 0)
	{
		retorno = ::write(fileDescriptor, (void*)(linea.c_str() + largoInicial - faltaEscribir), faltaEscribir);
		if (retorno == -1) throw std::ios_base::failure(strerror(errno));
		faltaEscribir -= retorno;
	}
	str("");
	return 0;
}

} /* namespace common */
