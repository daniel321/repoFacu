#ifndef SIGCERRABLE_H_
#define SIGCERRABLE_H_

#include "signals/BoolHandler.h"

const static int SigQuit = SIGUSR2;

/**
 * Clase para usar por herencia
 */

class SigCerrable
{
public:
	SigCerrable();
	virtual ~SigCerrable();
	const bool hayQueSalir() const;
private:
	BoolHandler quitHandler;
};

#endif /* SIGCERRABLE_H_ */
