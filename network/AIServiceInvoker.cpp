//invoker analyze protocol and unpack
//mlcai 2017-12-22

#include "Poco/MemoryStream.h"
#include "Poco/BinaryReader.h"
#include "Poco/BinaryWriter.h"
#include "AIServiceInvoker.h"
#include <QDebug>

AIServiceInvoker::AIServiceInvoker() : mPackState(RECVHEAD), mRecvBuff(0), mBuffSize(0)
{
//    mRecvBuff = new char[1024*1204*5];
//    memset(mRecvBuff, 0, 1024*1204*5);
}

bool AIServiceInvoker::invoke(char* data, int length, AIServiceHandler* handler)
{
	char* dataBuff = data;
	Poco::UInt32 dataSize = length;

	bool isNewData = false;
	if (0 != mBuffSize)
	{
		dataSize += mBuffSize;
		dataBuff = new char[dataSize];
		memcpy(dataBuff, mRecvBuff, mBuffSize);
		memcpy(dataBuff + mBuffSize, data, length);

		delete[] mRecvBuff;
		mRecvBuff = 0;
		mBuffSize = 0;

		isNewData = true;
	}

	char* dataPos = dataBuff;
	Poco::UInt32 leftSize = dataSize;

    static Poco::UInt64 recLength = 0;

	bool isEnough = true;
	while (isEnough)
	{
		switch (mPackState)
		{
		case RECVHEAD:
			{

                if (leftSize < mHeader.getHeadSize())
				{
					if (leftSize)
					{
						mBuffSize = leftSize;
						mRecvBuff = new char[mBuffSize];
						memcpy(mRecvBuff, dataPos, leftSize);
					}
					isEnough = false;
				}
				else
				{
                    Poco::MemoryInputStream binaryInStream(dataPos, mHeader.getHeadSize());
					Poco::BinaryReader reader(binaryInStream, Poco::BinaryReader::NETWORK_BYTE_ORDER);

                    reader >> mHeader.version();
                    reader >> mHeader.sn();
                    reader >> mHeader.sliceCount();
                    reader >> mHeader.sliceSn();
                    reader >> mHeader.sliceLength();
                    reader >> mHeader.length();
                    reader >> mHeader.msgLength();

                    dataPos += mHeader.getHeadSize();
                    leftSize -= mHeader.getHeadSize();
                    mPackState = RECVDATA;

//                    qDebug() << "AIHeader "
//                             << "sliceCount :"<< mHeader.sliceCount()
//                             << ",sliceLength: " << mHeader.sliceLength()
//                             <<", length:" << mHeader.length()
//                             <<",msgLength:"<<mHeader.msgLength()
//                             <<",sliceSln:"<<mHeader.sliceSn()
//                              <<",sn:"<<mHeader.sn();
				}
			}
			break;
		case RECVDATA:
			{
                if (leftSize < mHeader.sliceLength())
				{
					if (leftSize)
					{
						mBuffSize = leftSize;
						mRecvBuff = new char[mBuffSize];
						memcpy(mRecvBuff, dataPos, leftSize);
					}
					isEnough = false;
				}
				else
				{
                    unsigned int offset = 0;
                    if (mHeader.sliceCount() > 1)
					{
                        if (mPackSlices.size() == mHeader.sliceCount() - 1)
						{
                            char* totalData = new char[mHeader.length()];
							char* totalPos = totalData;
                            std::vector< std::pair<AIHeader, char*> >::iterator iter = mPackSlices.begin();
							for (; iter != mPackSlices.end(); ++iter)
							{
                                AIHeader& sliceHeader = iter->first;
                                memcpy(totalPos, iter->second, sliceHeader.sliceLength());
								delete[] iter->second;
                                totalPos += sliceHeader.sliceLength();
							}

							mPackSlices.clear();

                            memcpy(totalPos, dataPos, mHeader.sliceLength());


                            std::string msg(totalData, mHeader.msgLength());

                            invoke(mHeader, totalData, handler);

                            offset = mHeader.sliceLength();
						}
						else
						{
                            char* sliceData = new char[mHeader.sliceLength()];
                            memcpy(sliceData, dataPos, mHeader.sliceLength());

                            mPackSlices.push_back(std::pair<AIHeader, char*>(mHeader, sliceData));

                            offset = mHeader.sliceLength();
						}
					}
					else
                    {
                        invoke(mHeader, dataPos, handler);
                        offset = mHeader.length();
                    }

                    //qDebug() << "slice recive cnt = " << mPackSlices.size() << ", slice total cnt " << mHeader.sliceCount();

                    dataPos += offset;
                    leftSize -= offset;

                    memset(&mHeader, 0, mHeader.getHeadSize());

					mPackState = RECVHEAD;
				}

			}
			break;
		default:
			return false;
		}
	}

	if (isNewData)
		delete[] dataBuff;
}
