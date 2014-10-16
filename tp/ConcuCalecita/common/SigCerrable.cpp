#include "SigCerrable.h"

#include "../common/signals/SignalHandler.h"
#include "../common/exception/ErrnoWrap.h"

SigCerrable::SigCerrable()
{
	SignalHandler::getInstance()->registrarHandler(SigQuit, &quitHandler);
	int interrupt = siginterrupt(SigQuit, 1);
	if (interrupt == -1) throw Common::ErrnoWrap();
}

SigCerrable::~SigCerrable()
{

}

const bool SigCerrable::hayQueSalir() const
{
	return quitHandler.getBandera();
}

