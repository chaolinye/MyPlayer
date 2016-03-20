#ifndef DEALWEB_H
#define DEALWEB_H
#include<QString>
#include<QList>
#include"bloomfilter.h"
// extern QList<QString> urls;
// extern BloomFilter filter;


class dealWeb
{
public:
   dealWeb();

    QString  getHtml(QString url);
   void  getHtmlUrl(QString);

   void addUrl(QString);
   static QList<QString> *urls;
   static BloomFilter *filter;
   static bool isFirst;

};
  QString* matchKeywords(QString keyword);

#endif // DEALWEB_H
