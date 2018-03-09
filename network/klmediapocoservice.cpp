#include "klmediapocoservice.h"
#include "KLMessageHandler.h"
#include "sessionconnector.h"
#include "Poco/DOM/DOMParser.h"
#include "Poco/DOM/DOMWriter.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/Element.h"
#include "Poco/DOM/AutoPtr.h"
#include "Poco/DOM/NamedNodeMap.h"
#include "Poco/SAX/InputSource.h"
#include "Poco/XML/XMLWriter.h"
#include "Poco/DOM/Text.h"
#include <sstream>
#include <QDebug>

inline std::string convert2xml(const std::vector<std::pair<int, int>> &boundPoints,std::string &channelId)
{
    Poco::AutoPtr<Poco::XML::Document> pDocument = new Poco::XML::Document;

    Poco::AutoPtr<Poco::XML::Element> pRoot = pDocument->createElement("Subscribe");
    pRoot->setAttribute("Type", "DrawBoundMessage");

    Poco::AutoPtr<Poco::XML::Element> pChild = pDocument->createElement("Channel");
    pChild->setAttribute("ID", channelId);

    std::vector<std::pair<int, int>>::const_iterator it = boundPoints.begin();

    for(; it !=boundPoints.end(); it++)
    {
        Poco::AutoPtr<Poco::XML::Element> pSon = pDocument->createElement("Point");
        std::stringstream ssx;
        ssx << it->first;
        std::string x;
        ssx >> x;

        std::stringstream ssy;
        ssy << it->second;
        std::string y;
        ssy >> y;

        pSon->setAttribute("x", x);
        pSon->setAttribute("y", y);

        pChild->appendChild(pSon);
    }


    pRoot->appendChild(pChild);

    pDocument->appendChild(pRoot);

    Poco::XML::DOMWriter writer;
    std::ostringstream ostr;
    writer.writeNode(ostr, pDocument);

    return ostr.str();
}

inline std::string serarchConver2xml(std::string &channelId,std::string &startTimesec, std::string &endTimesec, std::string &type)
{
    Poco::AutoPtr<Poco::XML::Document> pDocument = new Poco::XML::Document;

    Poco::AutoPtr<Poco::XML::Element> pRoot = pDocument->createElement("Subscribe");
    pRoot->setAttribute("Type", "QueryAlarm");

    Poco::AutoPtr<Poco::XML::Element> pChild = pDocument->createElement("Channel");
    pChild->setAttribute("ID", channelId);

    Poco::AutoPtr<Poco::XML::Element> pSon = pDocument->createElement("Condition");

    pSon->setAttribute("type", type);
    pSon->setAttribute("start", startTimesec);
    pSon->setAttribute("end", endTimesec);

    pChild->appendChild(pSon);


    pRoot->appendChild(pChild);

    pDocument->appendChild(pRoot);

    Poco::XML::DOMWriter writer;
    std::ostringstream ostr;
    writer.writeNode(ostr, pDocument);

    return ostr.str();
}

KLMediaPocoService::KLMediaPocoService(int threadCount, SockReactor* reactor) : ThreadManager(threadCount, reactor)
{

}

void KLMediaPocoService::start()
{
    startAll();
}

void KLMediaPocoService::subScribe(std::string &ip, int port, std::string channelId)
{
    Net::SocketAddress addres(ip,port);
    SockConnector<KLMessageHandler> *connector = new SessionConnector<KLMessageHandler>(addres,channelId);

    SessionConnector<KLMessageHandler>::NewConnection cb= std::bind(&KLMediaPocoService::newConnect, this, std::placeholders::_1, std::placeholders::_2);

    (dynamic_cast<SessionConnector<KLMessageHandler>*>(connector))->setConnectionCB(cb);

    connector->registerConnector(*this);
}

void KLMediaPocoService::subScribeAlarm(std::string &ip, int port)
{
    Net::SocketAddress addres(ip,port);
    SockConnector<KLMessageHandler> *connector = new SessionConnector<KLMessageHandler>(addres,"*");

    SessionConnector<KLMessageHandler>::NewConnection cb= std::bind(&KLMediaPocoService::newConnect, this, std::placeholders::_1, std::placeholders::_2);

    (dynamic_cast<SessionConnector<KLMessageHandler>*>(connector))->setConnectionCB(cb);
    connector->registerConnector(*this);
}

void KLMediaPocoService::deleteHander(std::string &ip, int port, std::string &channelId)
{
    auto iter = std::find_if(_messageHandlerMap.begin(),_messageHandlerMap.end(),[&](const std::pair<KLMessageHandler*,std::vector<std::string>> &value){
        Poco::Net::SocketAddress oldAddres = value.first->serverSocket();
        std::string ipOld = oldAddres.host().toString();
        int portOld = oldAddres.port();
        if(ipOld == ip && portOld == port){
            std::vector<std::string> channelVec = value.second;
            for(auto p : channelVec){
                return p == channelId;
            }
        }
    });

    if(iter != _messageHandlerMap.end()){
        KLMessageHandler *hander = (*iter).first;
        _messageHandlerMap.erase(iter);
        if(hander){
            delete hander;
        }
    }
}

std::vector<QWidget *> KLMediaPocoService::waringWidgetVector() const
{
    return _notityWaringWidget;
}

void KLMediaPocoService::registerWaringWidget(QWidget *w)
{
    if(!w){
        std::cout << __LINE__ << " " << __FILE__ << " " << __func__ << std::endl;
        return;
    }

    _notityWaringWidget.push_back(w);
}

void KLMediaPocoService::searchWaring(std::pair<std::string, int> &serverAddress, std::string &channelId, std::string &startTime, std::string &endTime, std::string &type)
{
    KLMessageHandler *_pMessageHandler = getServiceHander(serverAddress, std::string("*"));
    if(!_pMessageHandler){
        return;
    }

    std::string xml = serarchConver2xml(channelId,startTime,endTime,type);
    AIHeader header;
    header.length() = xml.length();
    header.msgLength() = xml.length();
    header.sn() = std::rand();
    _pMessageHandler->send(header, const_cast<char*>(xml.c_str()), xml.length());
}

void KLMediaPocoService::setBoundPoints(std::pair<std::string, int> &serverAddress, std::string &channelId, const std::vector<std::pair<int, int>> &boundPoints)
{
    KLMessageHandler *_pMessageHandler = getServiceHander(serverAddress,channelId);
    if(!_pMessageHandler){
        return;
    }

    std::string xml = convert2xml(boundPoints,channelId);
    AIHeader header;
    header.length() = xml.length();
    header.msgLength() = xml.length();
    header.sn() = std::rand();

    _pMessageHandler->send(header, const_cast<char*>(xml.c_str()), xml.length());
}

void KLMediaPocoService::newConnect(KLMessageHandler* pKLMessageHandler, std::string channel)
{
    _messageHandlerMap[pKLMessageHandler].push_back(channel);
}

KLMessageHandler *KLMediaPocoService::getServiceHander(std::pair<std::string, int> &serverAddress, std::string &channelId) const
{
    for(auto value : _messageHandlerMap){
        Poco::Net::SocketAddress oldAddres = value.first->serverSocket();
        std::string ipOld = oldAddres.host().toString();
        int portOld = oldAddres.port();
        if(ipOld == serverAddress.first && portOld == serverAddress.second){
            std::vector<std::string> channelVec = value.second;
            for(auto p : channelVec){
                if(p == channelId){
                    return value.first;
                }
            }
        }
    }
    return nullptr;
}
