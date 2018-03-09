//define AIHeader for send data
//mlcai 2017-12-12

#ifndef AIHEADER_H
#define AIHEADER_H

#include "Poco/Types.h"

class AIHeader
{
public:
	AIHeader() 
	{
		mVer = 0x01;
		mSn = 0;
		mSliceCount = 0;
		mSliceSn = 0;
		mSliceLength = 0;
		mLength = 0;
		mMsgLength = 0;
	}
	~AIHeader()
	{
	}


	Poco::UInt16& version()
	{
		return mVer;
	}

	Poco::UInt32& sn()
	{
		return mSn;
	}

	Poco::UInt32& sliceCount()
	{
		return mSliceCount;
	}

	Poco::UInt32& sliceSn()
	{
		return mSliceSn;
	}

	Poco::UInt32& sliceLength()
	{
		return mSliceLength;
	}

	Poco::UInt32& length()
	{
		return mLength;
	}

	Poco::UInt32& msgLength()
	{
		return mMsgLength;
	}

	Poco::UInt32 getHeadSize()
	{
		return sizeof(mVer) + sizeof(mSn) + sizeof(mSliceCount) + sizeof(mSliceSn) + sizeof(mSliceLength) + sizeof(mLength) + sizeof(mMsgLength);
	}

	static Poco::UInt32 AIHEADSIZE;

private:
	Poco::UInt16 mVer; //0x01
	Poco::UInt32 mSn;   //----------------the slice have the same sn 
	Poco::UInt32 mSliceCount; //----------slice count----------------
	Poco::UInt32 mSliceSn; //-----------slice sequence number----------------
	Poco::UInt32 mSliceLength; //---------slice length-------------------
	Poco::UInt32 mLength;  //------------total body length include message and pictures' length-------------
	Poco::UInt32 mMsgLength; //----------message length without picture lenght
};

#endif
