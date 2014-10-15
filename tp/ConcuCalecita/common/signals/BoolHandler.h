#ifndef HANDLER_H_
#define HANDLER_H_

#include <signal.h>
#include <assert.h>	

#include "EventHandler.h"

/**
 * Handler que al recibir la señal setea un booleano
 */
class BoolHandler : public EventHandler {

	private:
		sig_atomic_t bandera;
	public:
		BoolHandler ();
		~BoolHandler ();
		virtual void handleSignal ( int signum );
		sig_atomic_t getBandera() const;
};

#endif
