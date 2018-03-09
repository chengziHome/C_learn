/*
 * KLServiceLogger.cpp
 *
 *  Created on: 2018-1-23
 *      Author: andy
 */

#include "KLServiceLogger.h"

KLServiceLogger KLServiceLogger::gServiceLogger;

KLServiceLogger::KLServiceLogger()
{
	// TODO Auto-generated constructor stub

}

KLServiceLogger::~KLServiceLogger()
{
	// TODO Auto-generated destructor stub
}

KLServiceLogger& KLServiceLogger::instance()
{
	return gServiceLogger;
}

void KLServiceLogger::set(KLServiceLog* servLog)
{
	mServiceLog = servLog;
}
