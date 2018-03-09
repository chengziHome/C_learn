/*
 * KLMessageSession.h
 *
 *  Created on: 2018-1-22
 *      Author: andy
 */

#ifndef KLMESSAGESESSION_H_
#define KLMESSAGESESSION_H_

#include "AIServiceInvoker.h"
#include "KLServiceLogger.h"
#include "Poco/Net/StreamSocket.h"
#include <map>

class KLMediaPocoService;

class KLMessageSession : public AIServiceInvoker
{
public:
    KLMessageSession(std::string channelId,KLMediaPocoService* mediaService);
	virtual ~KLMessageSession();

	void setServiceHandler(AIServiceHandler* handler);
    void setSocketAddress(Poco::Net::SocketAddress &addr);

    void subScribeAlarm(std::string &id);
    void subScribe(std::string &id);

private:
    void invoke(AIHeader &heander, char* body, AIServiceHandler* handler);

private:
    Poco::Net::SocketAddress _mAddres;
    std::string _channelId;
	AIServiceHandler* mServiceHandler = 0;
	KLMediaPocoService* mMediaService;

	KLServiceLogger& mSrvLog;

	Poco::UInt32 mSequence = 0;
};

#endif /* KLMESSAGESESSION_H_ */
