#ifndef KLMEDIAPOCOSERVICE_H
#define KLMEDIAPOCOSERVICE_H
#include "common/klmediaservice.h"
#include "Poco/Net/StreamSocket.h"
#include "LfReactor/SockNotification.h"
#include "LfReactor/SockConnector.h"
#include "LfReactor/ThreadManager.h"
#include <QWidget>
#include "AIHeader.h"

class KLMessageHandler;
class KLMediaPocoService : public MediaService,public ThreadManager
{
public:
    KLMediaPocoService(int threadCount, SockReactor* reactor);
    void start();
    void subScribe(std::string &ip,int port, std::string channelId);
    void subScribeAlarm(std::string &ip,int port);
    void deleteHander(std::string &ip,int port, std::string &channelId);
    std::vector<QWidget*> waringWidgetVector() const;
    void registerWaringWidget(QWidget*);
    void searchWaring(std::pair<std::string,int> &serverAddress,std::string &channelId,std::string &startTime, std::string &endTime, std::string &type);
    void setBoundPoints(std::pair<std::string,int> &serverAddress,std::string &channelId, const std::vector<std::pair<int, int> > &boundPoints);

private:
    void newConnect(KLMessageHandler* pKLMessageHandler, std::string channel);

    std::map<KLMessageHandler*, std::vector<std::string>> _messageHandlerMap;
    std::vector<QWidget*> _notityWaringWidget;

    KLMessageHandler* getServiceHander(std::pair<std::string,int> &serverAddress,std::string &channelId) const;
};

#endif // KLMEDIAPOCOSERVICE_H
