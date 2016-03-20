#include "dealweb.h"
#include "bloomfilter.h"
#include"BitContainer.h"
#include <QtCore>
#include <QtNetwork>
#include <iostream>
#include <QTextCodec>
#include <QString>
#include<QMessageBox>
#include<qdebug.h>
using namespace std;
//转码
#define G2U(s) ( QTextCodec::codecForName("GBK")->toUnicode(s) )
bool dealWeb::isFirst=true;
QList<QString>* dealWeb::urls=new QList<QString>();
BloomFilter* dealWeb::filter=new BloomFilter();
dealWeb::dealWeb()
{
    if(isFirst){
        //urls->append("http://www.iqiyi.com/");
        qDebug()<<"first init";
        isFirst=false;
    }
}
QString* matchKeywords(QString keyword)
{
    dealWeb x;
    QString url=dealWeb::urls->takeFirst();
    QString str=x.getHtml(url);
   x.getHtmlUrl(str);
   //qDebug()<<str;
    str= str.replace(QRegExp("</title>[\\s|\\S]*"),"");
     str= str.replace(QRegExp("[\\s|\\S]*<title>"),"");
    QRegExp rx(keyword);
    QString* a=new QString[2];
    a[0]="null";
    a[1]="";
    qDebug()<<"print str";
    qDebug()<<str;
    qDebug()<<"end print";
    if(str.contains(rx)){
        a[0]=str;
        a[1]=url;



   }
    qDebug()<<a[0];
    return a;

}
QString dealWeb::getHtml(QString url)
{

    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QNetworkReply *reply = manager->get(QNetworkRequest(QUrl(url)));
    QByteArray responseData;
    QString contentArea="";
    QEventLoop eventLoop;
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    eventLoop.exec();       //block until finish
    responseData=reply->readAll();
    contentArea=QString(responseData);
    qDebug()<<contentArea;
    qDebug()<<"getHtml";


    return contentArea;

}

void dealWeb::getHtmlUrl(QString content)
{

           QRegExp rx;
           rx.setMinimal(1);
           rx.setCaseSensitivity(Qt::CaseInsensitive);
           rx.setPattern("<a.*href=.*http(.*)>");

           int pos=0;
           while((pos=rx.indexIn(content,pos))!=-1)
           {
               QString webUrlArea=rx.cap(1);
               pos+=rx.matchedLength();
               int pos2=webUrlArea.indexOf("\"");
               webUrlArea=webUrlArea.left(pos2);
               QString a="http";

               a.append(webUrlArea);
                  //添加网址
                addUrl(a);
                qDebug()<<a;
                //qDebug()<<webUrlArea;
          }




}
void dealWeb:: addUrl(QString webUrlArea )
{

        QByteArray ba=webUrlArea.toLatin1();
        char* m=ba.data();
        if(filter->add(m))
           urls->append(webUrlArea);


}


