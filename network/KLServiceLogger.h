/*
 * KLServiceLogger.h
 *
 *  Created on: 2018-1-23
 *      Author: andy
 */

#ifndef KLSERVICELOGGER_H_
#define KLSERVICELOGGER_H_

#include <string>
#include <vector>
#include "Poco/Any.h"

class KLServiceLog
{
public:
	virtual ~KLServiceLog() {}

	virtual void log(const std::string& level, const std::string& fmt, const std::vector<Poco::Any>& args) = 0;

protected:
	KLServiceLog() {}
};

class KLServLogExtender
{
public:
	KLServLogExtender() {}
	~KLServLogExtender() {}

	void extend() {}

	template<class T, class...Args>
	void extend(T first, Args...args)
	{
		mAnys.push_back(first);
		extend(args...);
	}

	const std::vector<Poco::Any>& args()
	{
		return mAnys;
	}


private:
	std::vector<Poco::Any> mAnys;
};

class KLServiceLogger
{
public:
	virtual ~KLServiceLogger();

	static KLServiceLogger& instance();

	void set(KLServiceLog* servLog);

	template<class...Args>
	void log(const std::string& level, const std::string& fmt, Args...args)
	{
		if (mServiceLog)
		{
			KLServLogExtender extender;
			extender.extend(args...);
			mServiceLog->log(level, fmt, extender.args());
		}
	}

private:
	KLServiceLogger();
	KLServiceLog* mServiceLog = 0;
	static KLServiceLogger gServiceLogger;
};

#endif /* KLSERVICELOGGER_H_ */
