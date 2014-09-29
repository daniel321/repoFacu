#ifndef HANDLER_H_
#define HANDLER_H_

#include <signal.h>
#include <assert.h>	

#include "EventHandler.h"

class Handler : public EventHandler {

	private:
		sig_atomic_t bandera;
		int signal;

	public:

		Handler (int signum) : bandera(0),signal(signum) {
		}

		~Handler () {
		}

		virtual int handleSignal ( int signum ) {
			this->bandera = 1;
			return 0;
		}

		sig_atomic_t getBandera() const {
			return this->bandera;
		}

		int getSignalNumber() const {
			return this->bandera;
		}
};

#endif
