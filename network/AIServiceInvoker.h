//this defined invoker interface
//mlcai 2017-12-20

#ifndef AISERVICEINVOKER_H
#define AISERVICEINVOKER_H

#include <string>
#include <vector>
#include "AIHeader.h"
#include "AIServiceHandler.h"

class AIServiceInvoker
{
public:
    virtual ~AIServiceInvoker() {}

	virtual bool invoke(char* data, int length, AIServiceHandler* handler);

protected:
	AIServiceInvoker();

    virtual void invoke(AIHeader& heander, char* body, AIServiceHandler* handler) = 0;

private:
	enum PackageState
	{
		RECVHEAD,
		RECVDATA
	};

	PackageState mPackState;

	char* mRecvBuff;
	Poco::UInt32 mBuffSize;

    AIHeader mHeader;

	std::vector< std::pair<AIHeader, char*> > mPackSlices;
};

#endif
