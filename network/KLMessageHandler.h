/*
 * KLMessageHandler.h
 *
 *  Created on: 2018-1-22
 *      Author: andy
 */

#ifndef KLMESSAGEHANDLER_H_
#define KLMESSAGEHANDLER_H_

#include "Poco/Net/StreamSocket.h"
#include "LfReactor/SockNotification.h"
#include "LfReactor/ThreadManager.h"
#include "Poco/NotificationQueue.h"
#include "KLMessageSession.h"
#include "KLServiceLogger.h"

class KLMediaPocoService;

class KLMessageHandler: public AIServiceHandler
{
public:
    KLMessageHandler(Net::StreamSocket& sock, ThreadManager& thrMgr,std::string channelId);
    KLMessageHandler(Net::StreamSocket& sock, ThreadManager& thrMgr);
	virtual ~KLMessageHandler();

	void onReadable(ReadableNotification* pNotification);

	void onWritable(WritableNotification* pNotification);

    Net::SocketAddress serverSocket() const;
    KLMessageSession* messageSession() const;
    void setServerSocket(Net::SocketAddress);

	void sendPacket(char* data, int length);

private:
	class AIDataNotification: public Poco::Notification
	{
	public:
		AIDataNotification(char* buf, int length);
		~AIDataNotification();

		void getData(char* &data, int& length);

	private:
		char* mBuffer;
		int mLength;
	};

private:
    Net::StreamSocket mSock;
    Net::SocketAddress _serverSocket;

	char* mRecvBuffer;
	int mRecvSize;

	bool mIsSuspend = false;

	Poco::NotificationQueue mOutputQueue;

	char* mSendBuffer = 0;
	int mSendSize = 0;
	int mSendedSize = 0;

	KLMessageSession* mMessageSession;

	KLMediaPocoService* mMediaService;

	typedef void (KLMessageHandler::*DelFunction)();

	DelFunction mDeleteHandler = nullptr;
	Poco::Mutex mDelMutex;

	KLServiceLogger& mLogger;
};

#endif /* KLMESSAGEHANDLER_H_ */
