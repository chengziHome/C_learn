//IPC interface
//mlcai 2017-12-20

#ifndef AISERVICEHANDLER_H
#define AISERVICEHANDLER_H

#include "AIHeader.h"
class AIServiceInvoker;

class AIServiceHandler
{
public:
	virtual ~AIServiceHandler() {}

	virtual void send(AIHeader& head, char* data, int length);

	virtual void sendPacket(char* data, int length) = 0;

	void setInvoker(AIServiceInvoker* invoker)
	{
		mInvoker = invoker;
	}

protected:
	AIServiceHandler(AIServiceInvoker* invoker = 0) : mInvoker(invoker)
	{
	}

	AIServiceInvoker* mInvoker;
};

#endif
