/*
 * KLMessageHandler.cpp
 *
 *  Created on: 2018-1-22
 *      Author: andy
 */


#include "KLMessageHandler.h"
#include "KLMediaPocoService.h"

KLMessageHandler::KLMessageHandler(Net::StreamSocket& sock,
        ThreadManager& thrMgr, std::string channelId) :
		mSock(sock), mMediaService(dynamic_cast<KLMediaPocoService*>(&thrMgr)), mLogger(
				KLServiceLogger::instance())
{
	// TODO Auto-generated constructor stub

	mSock.setBlocking(false);

    mMessageSession = new KLMessageSession(channelId,mMediaService);
    mMessageSession->setSocketAddress(sock.address());
    mMessageSession->setServiceHandler(this);

    mRecvSize = 1024 * 1024 * 5;
	mRecvBuffer = new char[mRecvSize];
    memset(mRecvBuffer, 0, mRecvSize);

	mMediaService->addEventHandler(mSock,
			Observer<KLMessageHandler, ReadableNotification>(*this,
					&KLMessageHandler::onReadable));
	mMediaService->addEventHandler(mSock,
			Observer<KLMessageHandler, WritableNotification>(*this,
					&KLMessageHandler::onWritable));

}

KLMessageHandler::KLMessageHandler(Net::StreamSocket &sock, ThreadManager &thrMgr):
mSock(sock), mMediaService(dynamic_cast<KLMediaPocoService*>(&thrMgr)), mLogger(
        KLServiceLogger::instance())
{

}

KLMessageHandler::~KLMessageHandler()
{
	// TODO Auto-generated destructor stub
	mMediaService->removeEventHandler(mSock,
			Observer<KLMessageHandler, ReadableNotification>(*this,
					&KLMessageHandler::onReadable));
	mMediaService->removeEventHandler(mSock,
			Observer<KLMessageHandler, WritableNotification>(*this,
					&KLMessageHandler::onWritable));

	if (mMessageSession)
		delete mMessageSession;
}

void KLMessageHandler::onReadable(ReadableNotification* pNotification)
{
	pNotification->release();

	mMediaService->suspendEventHandler(mSock,
			Observer<KLMessageHandler, ReadableNotification>(*this,
					&KLMessageHandler::onReadable));
	mMediaService->promoteNewLeader();

	int readSize = 0;

	while (true)
	{
		try
		{
			readSize = mSock.receiveBytes(mRecvBuffer, mRecvSize);
			if (readSize < 0)
			{
                if (WSAGetLastError() == POCO_EAGAIN)
				{
					mMediaService->resumeEventHandler(mSock,
							Observer<KLMessageHandler, ReadableNotification>(
									*this, &KLMessageHandler::onReadable));
					return;
				}
			}

			if (readSize <= 0)
			{
				{
					Mutex::ScopedLock lock(mDelMutex);
					if (mDeleteHandler != nullptr)
						return;
					mDeleteHandler =
							(DelFunction) (&KLMessageHandler::onReadable);
				}
				delete this;
				return;
			}
		} catch (TimeoutException& e)
		{
			mMediaService->resumeEventHandler(mSock,
					Observer<KLMessageHandler, ReadableNotification>(*this,
							&KLMessageHandler::onReadable));
			return;
		} catch (Exception& e)
		{
			if (POCO_EWOULDBLOCK == e.code())
			{
				mMediaService->resumeEventHandler(mSock,
						Observer<KLMessageHandler, ReadableNotification>(*this,
								&KLMessageHandler::onReadable));
				return;
			}

			mLogger.log("error",
					"KLMessageHandler::onReadable catch exception msg %s or what %s",
					e.message(), e.what());
			{
				Mutex::ScopedLock lock(mDelMutex);
				if (mDeleteHandler != nullptr)
					return;
				mDeleteHandler = (DelFunction) (&KLMessageHandler::onReadable);
			}
			delete this;
			return;
		} catch (...)
		{
			mLogger.log("error",
					"KLMessageHandler::onReadable receiveBytes have exception!!!!");

			{
				Mutex::ScopedLock lock(mDelMutex);
				if (mDeleteHandler != nullptr)
					return;
				mDeleteHandler = (DelFunction) (&KLMessageHandler::onReadable);
			}
			delete this;
			return;
		}

		try
		{
			AIServiceInvoker* invoker = mMessageSession;
            invoker->invoke(mRecvBuffer, readSize, this);

		} catch (...)
		{
			mLogger.log("error",
					"KLMessageHandler::onReadable rtsp exception!!!!");

			{
				Mutex::ScopedLock lock(mDelMutex);
				if (mDeleteHandler != nullptr)
					return;
				mDeleteHandler = (DelFunction) (&KLMessageHandler::onReadable);
			}
			delete this;
			return;
		}
	}

}

void KLMessageHandler::onWritable(WritableNotification* pNotification)
{
	pNotification->release();

	mMediaService->suspendEventHandler(mSock,
			Observer<KLMessageHandler, WritableNotification>(*this,
					&KLMessageHandler::onWritable));
	mMediaService->promoteNewLeader();

	try
	{
        while (true)
        {
            int writeSize = 0;

            if (mSendSize)
            {
                try
                {
                    writeSize = mSock.sendBytes(mSendBuffer + mSendedSize,
                            mSendSize - mSendedSize);

                } catch (TimeoutException& e)
                {
                    mMediaService->resumeEventHandler(mSock,
                            Observer<KLMessageHandler, WritableNotification>(*this,
                                    &KLMessageHandler::onWritable));
                    return;
                } catch (Poco::Exception& ex)
                {
                    if (POCO_EWOULDBLOCK == ex.code())
                    {
                        mMediaService->resumeEventHandler(mSock,
                                Observer<KLMessageHandler, WritableNotification>(
                                        *this, &KLMessageHandler::onWritable));
                        return;
                    }

                    mLogger.log("error",
                            "KLMessageHandler::onWritable catch exception msg %s or what %s",
                            ex.message(), ex.what());
                    {
                        Poco::Mutex::ScopedLock lock(mDelMutex);
                        if (mDeleteHandler != nullptr)
                            return;
                        mDeleteHandler =
                                (DelFunction) (&KLMessageHandler::onWritable);
                    }
                    delete this;
                    return;
                }
            }

            if (mSendSize && writeSize <= 0)
            {
                {
                    Poco::Mutex::ScopedLock lock(mDelMutex);
                    if (mDeleteHandler != 0)
                        return;
                    mDeleteHandler = (DelFunction)(&KLMessageHandler::onWritable);
                }
                delete this;
                return;
            }

            mSendedSize += writeSize;

            if (mSendedSize < mSendSize)
            {
                mMediaService->resumeEventHandler(mSock,
                        Observer<KLMessageHandler, WritableNotification>(*this,
                                &KLMessageHandler::onWritable));
                return;
            }

            if (mSendBuffer)
            {
                delete[] mSendBuffer;
                mSendBuffer = 0;
            }
            mSendSize = mSendedSize = 0;

            Poco::AutoPtr<AIDataNotification> pNotif = dynamic_cast<AIDataNotification*>(mOutputQueue.dequeueNotification());
            if (nullptr == pNotif.get())
            {
                mIsSuspend = true;
                return;
            }

            pNotif->getData(mSendBuffer, mSendSize);
        }


	} catch (Poco::Exception& e)
	{
		mLogger.log("error",
				"KLMessageHandler::onWritable have exception message%s or what %s!!!!",
				e.message(), std::string(e.what()));
	} catch (std::exception& exp)
	{
		mLogger.log("error",
				"KLMessageHandler::onWritable have exception %s!!!!",
				std::string(exp.what()));
	} catch (...)
	{
		mLogger.log("error", "KLMessageHandler::onWritable have exception!!!!");
    }
}

Net::SocketAddress KLMessageHandler::serverSocket() const
{
    return _serverSocket;
}

KLMessageSession *KLMessageHandler::messageSession() const
{
    return mMessageSession;
}

void KLMessageHandler::setServerSocket(Net::SocketAddress s)
{
    _serverSocket = s;
}

void KLMessageHandler::sendPacket(char* data, int length)
{
	mOutputQueue.enqueueNotification(new AIDataNotification(data, length));

	if (mIsSuspend)
	{
		mIsSuspend = false;
		mMediaService->resumeEventHandler(mSock,
				Observer<KLMessageHandler, WritableNotification>(*this,
						&KLMessageHandler::onWritable));
	}
}

KLMessageHandler::AIDataNotification::AIDataNotification(char* buf, int length) :
		mLength(length)
{
	mBuffer = new char[length];
	memcpy(mBuffer, buf, mLength);
}

KLMessageHandler::AIDataNotification::~AIDataNotification()
{
	if (mBuffer)
		delete[] mBuffer;
}

void KLMessageHandler::AIDataNotification::getData(char* &data, int& length)
{
	length = mLength;
	data = new char[length];
	memcpy(data, mBuffer, length);
}
