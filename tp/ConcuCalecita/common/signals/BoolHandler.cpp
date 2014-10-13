#include "BoolHandler.h"

BoolHandler::BoolHandler (int signum) : bandera(0) {}

BoolHandler::~BoolHandler () {}

void BoolHandler::handleSignal ( int signum )
{
	this->bandera = 1;
}

sig_atomic_t BoolHandler::getBandera() const
{
	return this->bandera;
}

