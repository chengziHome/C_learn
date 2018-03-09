#ifndef SESSIONCONNECTOR_H
#define SESSIONCONNECTOR_H

#include "LfReactor/SockConnector.h"
#include "playwindow/videoplayer/videoplayer.h"
#include "KLMessageHandler.h"
#include <functional>

template<class ServiceHandler>
class SessionConnector : public SockConnector<ServiceHandler>
{
public:
    typedef std::function<void(ServiceHandler*, std::string)> NewConnection;

public:
    explicit SessionConnector(Poco::Net::SocketAddress& address,std::string channel):SockConnector<ServiceHandler>(address),_serviceHandler(nullptr){
        _mAddres = address;
        _channel = channel;
    }

    void setConnectionCB(NewConnection cb)
    {
        _cb = cb;
    }

protected:
    ServiceHandler* createServiceHandler(){

        _serviceHandler = new ServiceHandler(dynamic_cast<Poco::Net::StreamSocket&>(socket()),*thrMgr(),_channel);
        KLMessageHandler * hander = dynamic_cast<KLMessageHandler*>(_serviceHandler);
        if(hander){
            hander->setServerSocket(_mAddres);
            hander->messageSession()->setSocketAddress(_mAddres);
        }
        if(_cb)
        {
            _cb(_serviceHandler, _channel);
        }
        return _serviceHandler ;
    }

private:
    std::string _channel;

   Net::SocketAddress _mAddres;
   ServiceHandler   *_serviceHandler;
   NewConnection _cb;
};
#endif // SESSIONCONNECTOR_H
