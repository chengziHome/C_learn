/*
 * AIServiceHandler.cpp
 *
 *  Created on: 2018-1-23
 *      Author: andy
 */

#include "Poco/NumberFormatter.h"
#include "Poco/MemoryStream.h"
#include "Poco/BinaryReader.h"
#include "Poco/BinaryWriter.h"
#include "AIServiceHandler.h"

const int MAX_SEND_SIZE = 1024;

void AIServiceHandler::send(AIHeader& head, char* data, int length)
{
	char* pos = data;
	int packageSize = length;

	int sliceSn = 0;
    int sliceMaxSizeCount = length / MAX_SEND_SIZE;
    int sliceCount = sliceMaxSizeCount;
    if (length % MAX_SEND_SIZE)
        sliceCount += 1;

    for (int i = 0; i < sliceMaxSizeCount; ++i)
	{
		AIHeader sliceHead;
		sliceHead.sn() = head.sn();
		sliceHead.sliceCount() = sliceCount;
		sliceHead.sliceSn() = sliceSn++;
		sliceHead.sliceLength() = MAX_SEND_SIZE;
		sliceHead.length() = head.length();
		sliceHead.msgLength() = head.msgLength();

		char* buff = new char[AIHeader::AIHEADSIZE + sliceHead.sliceLength()];

		Poco::MemoryOutputStream output(buff,
				AIHeader::AIHEADSIZE + sliceHead.sliceLength());
		Poco::BinaryWriter writer(output,
				Poco::BinaryWriter::NETWORK_BYTE_ORDER);

		writer << sliceHead.version();
		writer << sliceHead.sn();
		writer << sliceHead.sliceCount();
		writer << sliceHead.sliceSn();
		writer << sliceHead.sliceLength();
		writer << sliceHead.length();
		writer << sliceHead.msgLength();

		writer.writeRaw(pos, MAX_SEND_SIZE);
		pos += MAX_SEND_SIZE;
		packageSize -= MAX_SEND_SIZE;

		sendPacket(buff, AIHeader::AIHEADSIZE + sliceHead.sliceLength());

		delete[] buff;
	}

	if (packageSize)
	{
		AIHeader sliceHead;
		sliceHead.sn() = head.sn();
		sliceHead.sliceCount() = sliceCount;
		sliceHead.sliceSn() = sliceSn;
		sliceHead.sliceLength() = packageSize;
		sliceHead.length() = head.length();
		sliceHead.msgLength() = head.msgLength();

		char* buff = new char[AIHeader::AIHEADSIZE + sliceHead.sliceLength()];

		Poco::MemoryOutputStream output(buff,
                AIHeader::AIHEADSIZE + sliceHead.sliceLength());
		Poco::BinaryWriter writer(output,
				Poco::BinaryWriter::NETWORK_BYTE_ORDER);

		writer << sliceHead.version();
		writer << sliceHead.sn();
		writer << sliceHead.sliceCount();
		writer << sliceHead.sliceSn();
		writer << sliceHead.sliceLength();
		writer << sliceHead.length();
		writer << sliceHead.msgLength();


        writer.writeRaw(pos, packageSize);

		sendPacket(buff, AIHeader::AIHEADSIZE + sliceHead.sliceLength());

		delete[] buff;
	}
}

