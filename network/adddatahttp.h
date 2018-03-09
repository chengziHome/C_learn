#ifndef ADDDATAHTTP_H
#define ADDDATAHTTP_H

#include <QObject>
QT_FORWARD_DECLARE_CLASS(QThread)
QT_FORWARD_DECLARE_CLASS(QWidget)
class AddDataHttp : public QObject
{
    Q_OBJECT
public:
    enum SourceType{
        Image,
        Video
    };
    AddDataHttp(QObject *parent = nullptr);
    ~AddDataHttp();

signals:
    void sigTotalFrame(QWidget*, int);
    void sigCurrentFrame(QWidget*, int);

public slots:
    void slotPostPerson(QWidget*, QString,int,QString);

private:
    QThread *_mThread;
    QString _trainHost;
    QWidget *_mWidget = nullptr;
    int _currentFrame = 0;
    void postImage(QString &host, QByteArray& data);
    void postTrain();
};

#endif // ADDDATAHTTP_H
