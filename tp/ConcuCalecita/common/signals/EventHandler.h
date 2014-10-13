#ifndef EVENTHANDLER_H_
#define EVENTHANDLER_H_

class EventHandler {

public:
	virtual void handleSignal ( int signum ) = 0;
	virtual ~EventHandler () {};
};

#endif /* EVENTHANDLER_H_ */
