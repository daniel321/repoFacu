#include "LogStreamBuf.h"

#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <iostream>
#include "../exception/ErrnoWrap.h"

namespace Common
{

LogStreamBuf::LogStreamBuf(const char* path) : fileDescriptor(0)
{
	fileDescriptor = ::open(path, O_WRONLY | O_APPEND | O_CREAT, 0666);
	if (fileDescriptor == -1) throw Common::ErrnoWrap();
}

LogStreamBuf::~LogStreamBuf()
{
	if (fileDescriptor != 0) close(fileDescriptor);
}

std::string LogStreamBuf::timestamp()
{
	time_t fecha = ::time(0);
	std::string strFecha(::asctime(::localtime(&fecha)));
	strFecha.erase(strFecha.length()-1, 1); // Borramos el \n
	return strFecha;
}

int LogStreamBuf::sync ()
{
	std::string linea("["+timestamp()+"] "+str());
	ssize_t retorno = 0;
	ssize_t largoInicial = linea.length();
	ssize_t faltaEscribir = linea.length();
	while (faltaEscribir > 0)
	{
		retorno = ::write(fileDescriptor, (void*)(linea.c_str() + largoInicial - faltaEscribir), faltaEscribir);
		if (retorno == -1) throw Common::ErrnoWrap();
		faltaEscribir -= retorno;
	}
	retorno = ::fsync(fileDescriptor);
	if (retorno == -1) throw Common::ErrnoWrap();
	str("");
	return 0;
}

} /* namespace common */
