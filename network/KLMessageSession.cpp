/*
 * KLMessageSession.cpp
 *
 *  Created on: 2018-1-22
 *      Author: andy
 */

#include "KLMessageSession.h"
#include "Poco/Observer.h"
#include "Poco/NumberFormatter.h"
#include "Poco/MemoryStream.h"
#include "Poco/BinaryReader.h"
#include "Poco/BinaryWriter.h"
#include "Poco/DOM/DOMParser.h"
#include "Poco/DOM/DOMWriter.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/Element.h"
#include "Poco/DOM/AutoPtr.h"
#include "Poco/SAX/InputSource.h"
#include "Poco/XML/XMLWriter.h"
#include "Poco/DOM/Text.h"
#include "Poco/NumberParser.h"
#include "Poco/DOM/NamedNodeMap.h"
#include <fstream>
#include <sstream>
#include "waringevent.h"
#include "klmediapocoservice.h"
#include <QCoreApplication>
#include "playwindow/videoplayermanager/videoplayermanager.h"
#include <QDebug>

int getOnAlgorithmData(Poco::XML::Node* pNode, std::vector<std::pair<int,int>> &boundPoints)
{
    Poco::XML::Node* child = pNode->firstChild();
    if(std::string("Channel") != child->nodeName()){
        throw("DrawBoundMessage node name is not Channel");
    }

    if (!child->hasAttributes())
    {
        throw("DrawBoundMessage Channel Node no attributes");
    }

    Poco::XML::NamedNodeMap *pAttriMap = child->attributes();

    if(1 != pAttriMap->length())
    {
        throw("DrawBoundMessage Channel Node  attributes number not equal 1");
    }

    Poco::XML::Node *pattri = pAttriMap->item(0);
    std::string attrName = pattri->localName();
    if(std::string("ID") != attrName)
    {
        throw("DrawBoundMessage Channel Node  attributes name  not equal ID");
    }

    std::string attrValue = pattri->nodeValue();

    int channleId = Poco::NumberParser::parse(attrValue);


    Poco::XML::Node *grandChild = child->firstChild();


    while (grandChild) {
        if(grandChild->nodeName() == "Point"){

            if (!grandChild->hasAttributes())
            {
                throw("DrawBoundMessage Channel Node  No Point");
            }

            Poco::XML::NamedNodeMap *pAttriMap = grandChild->attributes();

            if(2 != pAttriMap->length())
            {
                throw("DrawBoundMessage Channel Node  Point coordinate number is not 2");;
            }

            std::pair<int,int> point;

            Poco::XML::Node *pattri = pAttriMap->item(0);
            std::string attrName = pattri->localName();
            if(std::string("x") == attrName)
            {
                point.first = Poco::NumberParser::parse(pattri->nodeValue());
            }

            pattri = pAttriMap->item(1);
            attrName = pattri->localName();
            if(std::string("y") == attrName)
            {
                point.second = Poco::NumberParser::parse(pattri->nodeValue());
            }

            boundPoints.push_back(point);
        }
        grandChild = grandChild->nextSibling();
    }

    return channleId;
}

KLMessageSession::KLMessageSession(std::string channelId, KLMediaPocoService* mediaService) : mMediaService(mediaService),
mSrvLog(KLServiceLogger::instance()),_channelId(channelId)
{
	// TODO Auto-generated constructor stub

}

KLMessageSession::~KLMessageSession()
{
    // TODO Auto-generated destructor stub
}

void KLMessageSession::setServiceHandler(AIServiceHandler* handler)
{
	mServiceHandler = handler;
    mServiceHandler->setInvoker(this);
    if(_channelId == "*"){
        subScribeAlarm(_channelId);
    }else{
        subScribe(_channelId);
    }
}

void KLMessageSession::setSocketAddress(Net::SocketAddress &addr)
{
    _mAddres = addr;
}

void KLMessageSession::subScribeAlarm(std::string &id)
{
    Poco::XML::AutoPtr<Poco::XML::Document> pDoc(new Poco::XML::Document);

    Poco::XML::AutoPtr<Poco::XML::Element> pNotifRoot = pDoc->createElement("Subscribe");
    pNotifRoot->setAttribute("Type", "Alarming");
    pDoc->appendChild(pNotifRoot);

    Poco::XML::AutoPtr<Poco::XML::Element> pChannelId = pDoc->createElement("ChannelId");
    pNotifRoot->appendChild(pChannelId);
    Poco::XML::AutoPtr<Poco::XML::Text> pText = pDoc->createTextNode(id);
    pChannelId->appendChild(pText);


    std::ostringstream ostr;

    Poco::XML::DOMWriter writer;
    writer.setNewLine("\n");
    writer.setOptions(Poco::XML::XMLWriter::PRETTY_PRINT);
    writer.writeNode(ostr, pDoc);

    std::string msgStr = ostr.str();

    mSrvLog.log("debug", "KLMessageSession::onDetection message: %s", msgStr);

    AIHeader header;
    header.sn() = mSequence++;
    header.length() = msgStr.size();
    header.msgLength() = msgStr.size();

    if (mServiceHandler)
        mServiceHandler->send(header, const_cast<char*>(msgStr.c_str()), msgStr.size());
}

void KLMessageSession::subScribe(std::string &id)
{
    Poco::XML::AutoPtr<Poco::XML::Document> pDoc(new Poco::XML::Document);

    Poco::XML::AutoPtr<Poco::XML::Element> pNotifRoot = pDoc->createElement("Subscribe");
    pNotifRoot->setAttribute("Type", "ChannelMessage");
    pDoc->appendChild(pNotifRoot);

    Poco::XML::AutoPtr<Poco::XML::Element> pChannelId = pDoc->createElement("ChannelId");
    pNotifRoot->appendChild(pChannelId);
    Poco::XML::AutoPtr<Poco::XML::Text> pText = pDoc->createTextNode(id);
    pChannelId->appendChild(pText);


    std::ostringstream ostr;

    Poco::XML::DOMWriter writer;
    writer.setNewLine("\n");
    writer.setOptions(Poco::XML::XMLWriter::PRETTY_PRINT);
    writer.writeNode(ostr, pDoc);

    std::string msgStr = ostr.str();

    mSrvLog.log("debug", "KLMessageSession::onDetection message: %s", msgStr);

    AIHeader header;
    header.sn() = mSequence++;
    header.length() = msgStr.size();
    header.msgLength() = msgStr.size();

    if (mServiceHandler)
        mServiceHandler->send(header, const_cast<char*>(msgStr.c_str()), msgStr.size());
}

void KLMessageSession::invoke(AIHeader& heander, char* body, AIServiceHandler* handler)
{
    unsigned long imgLen = heander.length() - heander.msgLength();
    unsigned char *pImgData = new unsigned char[imgLen];
    memcpy(pImgData, reinterpret_cast<unsigned char*>(body) + heander.msgLength(), imgLen);

    std::string str(body, heander.msgLength());

	std::istringstream istr(str);

	Poco::XML::DOMParser parser;
	parser.setFeature(Poco::XML::DOMParser::FEATURE_FILTER_WHITESPACE, true);
    //parser.setFeature(Poco::XML::XMLReader::FEATURE_NAMESPACE_PREFIXES, false);
	Poco::XML::InputSource source(istr);

	Poco::XML::AutoPtr<Poco::XML::Document> pDoc = parser.parse(&source);

    Poco::XML::Element* pElem = pDoc->documentElement();
    if (pElem->nodeName() == "Notify")
	{
		std::string type;
		Poco::XML::Node* child = pElem->firstChild();
		if (child)
		{
            if (pElem->getAttribute("Type") == "DetectBoxes")
            {
                child = child->firstChild();
                std::list<KLRect> boxesList;
                while (child) {
                    if(child->nodeName() == "Box"){
                        Poco::XML::Element *element = nullptr;
                        try{
                            element = dynamic_cast<Poco::XML::Element*>(child);
                        }catch (std::exception &e){
                            std::cout << e.what();
                        }
                        if(element){
                            int category = Poco::NumberParser::parse(element->getAttribute("category"));
                            int left = Poco::NumberParser::parse(element->getAttribute("left"));
                            int top = Poco::NumberParser::parse(element->getAttribute("top"));
                            int right = Poco::NumberParser::parse(element->getAttribute("right"));
                            int bottom = Poco::NumberParser::parse(element->getAttribute("bottom"));
                            KLRect klRect;
                            klRect.x = left;
                            klRect.y = top;
                            klRect.width = right -left;
                            klRect.height = bottom - top;
                            boxesList.push_back(klRect);
                        }
                    }
                    child = child->nextSibling();
                }
                VideoPlayer *player = VideoPlayerManager::instance()->findVideoPlayer(std::make_pair(_mAddres.host().toString(),static_cast<int>(_mAddres.port())),_channelId);
                if(player){
                    player->setBoxs(boxesList);
                }
            }
            else if(pElem->getAttribute("Type") == "Alarming"){
                child = pElem->firstChild();
                if(child->nodeName() != std::string("Alarming")){
                    return;
                }

                Poco::XML::Element *element = nullptr;
                try{
                    element = dynamic_cast<Poco::XML::Element*>(child);
                }catch(std::exception &e){
                    std::cout << e.what();
                    return;
                }

                int type = Poco::NumberParser::parse(element->getAttribute("type"));
                unsigned int channelId = Poco::NumberParser::parse(element->getAttribute("channelID"));

                std::string timestampStr = element->getAttribute("stamp");
                std::string opt = element->getAttribute("opt"); //opt == subscribe opt = query

                qDebug() << QString::fromStdString(str);
//                timestampStr.erase(0, timestampStr.find_first_not_of(" "));
//                timestampStr.erase(timestampStr.find_last_not_of(" ") + 1);

                Poco::XML::Node *childChild = child->firstChild();
                std::vector<unsigned long> _vecImgLeng;

                while (childChild) {
                    if(childChild->nodeName() == "Picture"){
                        Poco::XML::Element *element = nullptr;
                        try{
                            element = dynamic_cast<Poco::XML::Element*>(childChild);
                        }catch (std::exception &e){
                            std::cout << e.what();
                            return;
                        }
                        if(element){
                            std::string strlength = element->getAttribute("length");
                            std::stringstream ss;
                            ss << strlength;
                            unsigned long imgLength = 0;
                            ss >> imgLength;

                            _vecImgLeng.push_back(imgLength);
                        }
                    }
                    childChild = childChild->nextSibling();
                }

                for(auto p : mMediaService->waringWidgetVector()){
                    WaringImageEvent *imgEvent = new WaringImageEvent(QEvent::Type(KLMessage));
                    imgEvent->setOption(opt);
                    imgEvent->setChannelId(channelId);
                    imgEvent->setWaringType(type);
                    imgEvent->setTime(timestampStr);

                    std::vector<unsigned long>::iterator it = _vecImgLeng.begin();
                    unsigned long offset = 0;
                    for(; it != _vecImgLeng.end(); it++)
                    {
                        unsigned long len = *it;
                        std::string imgData;
                        imgData.assign(reinterpret_cast<char*>(pImgData) + offset,len);
                        imgEvent->addImg(std::make_pair(imgData,std::string("jpg")));
                        offset += *it;
                    }

                    imgEvent->setServerAddres(_mAddres.host().toString(),static_cast<int>(_mAddres.port()));
                    QCoreApplication::postEvent(p,imgEvent);
                }
            }
            else if(pElem->getAttribute("Type") == "DrawBoundMessage"){
                std::vector<std::pair<int,int>> boundPoints;

                int channelId = 0;
                try
                {
                    channelId = ::getOnAlgorithmData(pElem, boundPoints);
                    std::stringstream ss;
                    ss << channelId;
                    std::string channelStr;
                    ss >> channelStr;
                    VideoPlayerManager::instance()->updateDrawBox(std::make_pair(_mAddres.host().toString(),static_cast<int>(_mAddres.port())),channelStr,boundPoints);
                }
                catch(std::string &e)
                {
                    mSrvLog.log("info", "KLMessageSession::invoke DrawBoundMessage failed %s", e);
                }
            }
		}
	}
}

