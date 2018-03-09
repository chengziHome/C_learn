#ifndef WARINGMESSAGEEVENT_H
#define WARINGMESSAGEEVENT_H
#include <QEvent>
#include <vector>

enum WaringEventType{
    KLMessage = QEvent::User
};

class WaringImageEvent : public QEvent
{
public:
    WaringImageEvent(Type);
    void setWaringType(int);
    void addImg(std::pair<std::string,std::string> &);
    void setChannelId(unsigned long);
    void setServerAddres(std::string&, int);
    void setTime(std::string &);
    void setOption(std::string&);

    int waringType() const;
    void getImageVec(std::vector<std::pair<std::string,std::string>> &);
    void serverAddress(std::string &,int&);
    unsigned long channelId() const;
    std::string time() const;
    std::string option() const;

private:
    int _waringType = -1,_serverPort = -1;
    std::string  _serverIp,_opt,_time;
    std::vector<std::pair<std::string,std::string>> _imgVec;
    unsigned long _channelId = -1;
};
#endif // WARINGMESSAGEEVENT_H
