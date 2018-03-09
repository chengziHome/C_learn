#include "waringevent.h"

WaringImageEvent::WaringImageEvent(QEvent::Type type):
    QEvent(type)
{
}

void WaringImageEvent::setWaringType(int t)
{
    _waringType = t;
}

void WaringImageEvent::addImg(std::pair<std::string,std::string> &v)
{
    _imgVec.push_back(v);
}

void WaringImageEvent::setChannelId(unsigned long id)
{
    _channelId = id;
}

void WaringImageEvent::setServerAddres(std::string &ip, int p)
{
    _serverIp = ip;
    _serverPort = p;
}

void WaringImageEvent::setTime(std::string & t)
{
    _time = t;
}

void WaringImageEvent::setOption(std::string &o)
{
    _opt = o;
}

int WaringImageEvent::waringType() const
{
    return _waringType;
}

void WaringImageEvent::getImageVec(std::vector<std::pair<std::string,std::string>> &v)
{
    v = _imgVec;
}

void WaringImageEvent::serverAddress(std::string &ip, int &port)
{
    ip = _serverIp;
    port = _serverPort;
}

unsigned long WaringImageEvent::channelId() const
{
    return _channelId;
}

std::string WaringImageEvent::time() const
{
    return _time;
}

std::string WaringImageEvent::option() const
{
    return _opt;
}
