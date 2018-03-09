#include "adddatahttp.h"
#include <QDir>
#include <QImage>
#include <QFile>
#include <QBuffer>
#include <QFileInfoList>
#include <curl/curl.h>
#include <QDateTime>
#include <QThread>
#include <QDebug>
#include <opencv2/opencv.hpp>

AddDataHttp::AddDataHttp(QObject *parent):
    QObject(parent)
{
    _mThread = new QThread;
    moveToThread(_mThread);
}

AddDataHttp::~AddDataHttp()
{
    _mThread->quit();
    _mThread->wait();
}

void AddDataHttp::slotPostPerson(QWidget *w, QString path, int type, QString host)
{
    _mWidget = w;
    _trainHost = host;
    _currentFrame = 0;
    if(type == Image){
        QDir dir(path);
        QFileInfoList fileList = dir.entryInfoList(QDir::Files);
        emit sigTotalFrame(_mWidget, fileList.size());
        foreach (QFileInfo fileInfo, fileList) {
            QFile file(fileInfo.filePath());
            if(file.open(QIODevice::ReadOnly)){
                QThread::msleep(300);
                postImage(_trainHost, file.readAll());
                file.close();
            }
        }
    }else if(type == Video){
        cv::VideoCapture capture;
        QByteArray videoPathArray = path.toLatin1();
        char *videoPath = videoPathArray.data();
        if(!capture.open(videoPath)){
            return;
        }

        int totalCount = static_cast<int>(capture.get(CV_CAP_PROP_FRAME_COUNT));
        emit sigTotalFrame(_mWidget,totalCount);
        cv::Mat frame;
        while (true) {
            capture >> frame;
            cv::cvtColor(frame,frame,CV_BGR2RGB);
            QImage img((const uchar *)frame.data,frame.cols,frame.rows,frame.step,QImage::Format_RGB888);

            QByteArray arr;
            QBuffer buffer(&arr);
            if(!buffer.open(QIODevice::WriteOnly)){
                continue;
            }
            img.save(&buffer,".jpg");
            postImage(_trainHost,arr);
            if(frame.empty()){
                emit sigCurrentFrame(_mWidget,totalCount);
                break;
            }
        }
    }

    postTrain();
}

static size_t resposeImage(void *ptr, size_t size, size_t nmemb, void *userData)
{
    QByteArray arr(reinterpret_cast<char*>(ptr));
    AddDataHttp *obj = reinterpret_cast<AddDataHttp*>(userData);
    if(!obj){
        goto END;
    }

//    qDebug() << "server response" << arr << __FILE__ << __LINE__;
END:
    return size * nmemb;
}

void AddDataHttp::postImage(QString &host, QByteArray &data)
{
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    if(curl){
        struct curl_slist *headers = nullptr;
        headers = curl_slist_append(headers,"Content-Type:Content-Type:application/json;charset=UTF-8");
        headers = curl_slist_append(headers, "Expect:");
        curl_easy_setopt(curl,CURLOPT_HTTPHEADER,headers);
        curl_easy_setopt(curl, CURLOPT_POST, 1); //作用POST

        int tt = QDateTime::currentDateTime().toMSecsSinceEpoch();
        QString urlStr = QString(host + QString("/addsample.json?id=%1").arg(tt,10));
        QByteArray urlByteArr = urlStr.toLatin1();
        char *pUrl = urlByteArr.data();
        curl_easy_setopt(curl, CURLOPT_URL, pUrl);   // 指定url

        char *p = data.data();
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, p);    // 指定post内容
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, data.size());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, ::resposeImage);
        curl_easy_setopt(curl,CURLOPT_WRITEDATA, const_cast<AddDataHttp*>(this));
//        curl_easy_setopt(curl, CURLOPT_TIMEOUT,60);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK){
            qDebug() << curl_easy_strerror(res);
        }else{
            emit sigCurrentFrame(_mWidget,++_currentFrame);
        }
        curl_easy_cleanup(curl);
    }
}

void AddDataHttp::postTrain()
{
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    if(curl){
        struct curl_slist *headers = nullptr;
        headers = curl_slist_append(headers,"Content-Type:Content-Type:application/json;charset=UTF-8");
        headers = curl_slist_append(headers, "Expect:");
        curl_easy_setopt(curl,CURLOPT_HTTPHEADER,headers);
        curl_easy_setopt(curl, CURLOPT_POST, 1); //作用POST

        QString urlStr = QString(_trainHost + QString("/train.json"));
        QByteArray urlByteArr = urlStr.toLatin1();
        char *pUrl = urlByteArr.data();
        curl_easy_setopt(curl, CURLOPT_URL, pUrl);   // 指定url

        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "");    // 指定post内容
//        curl_easy_setopt(curl, CURLOPT_TIMEOUT,60);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK){
            qDebug() << curl_easy_strerror(res);
        }
        curl_easy_cleanup(curl);
    }
}
