#ifndef VOIDHANDLER_H_
#define VOIDHANDLER_H_

#include "EventHandler.h"

/**
 * Clase que no hace nada, a ser usada para triggerear interrupts
 */
class VoidHandler: public EventHandler
{
public:
	VoidHandler() {}
	virtual ~VoidHandler() {}
	void handleSignal(int signum) {}
};

#endif /* VOIDHANDLER_H_ */
