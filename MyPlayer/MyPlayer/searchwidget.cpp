#include "searchwidget.h"
#include "dealweb.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPalette>
#include <QHeaderView>
#include <QScrollBar>
#include <QDebug>
#include<QMessageBox>
SearchWidget::SearchWidget(QWidget *parent) :
    QWidget(parent)
{
    searchLine=new QLineEdit(this);
    searchLine->setMaximumWidth(600);
    searchLine->setMinimumHeight(30);
    searchLine->setTextMargins(0, 1, 32, 1);
    //搜索栏美化样式表
    searchLine->setStyleSheet("QLineEdit{font: bold  large \"Times New Roman\";font-size:18px;color:rgb(55,100,255);height:20px;border:4px solid rgb(155,200,33);border-radius:1px;selection-color:pink}"
                         "QLineEdit{ border: 0px groove rgb(255,0,0);color:rgb(201,201,201);  background-color: rgb(36,37, 39);}"
                         "QLineEdit:hover{ border: 2px groove rgb(26,58,93);color:rgb(201,201,201);  background-color: rgb(36,37, 39); }"
                         "QLineEdit:!hover{border: 2px groove rgb(36,37, 39);color:rgb(75,79, 81);  background-color: rgb(36,37, 39);}"
                         "QLineEdit:focus {border: 9px groove rgb(0,0,255);color:rgb(0,0,255);  background-color: rgb(36,37, 39););}"
                              );
    searchLine->setPlaceholderText("请输入要看视频名~");

    searchBtn=new QPushButton(this);
    searchBtn->setFixedSize(18,18);
    searchBtn->setCursor(Qt::PointingHandCursor);
    searchBtn->setStyleSheet("QPushButton{border-image: url(:/images/searchBtn01);}"
                             "QPushButton:hover{border-image: url(:/images/searchBtn02);}"
                             "QPushButton:pressed{border-image: url(:/images/searchBtn03);}");

    //搜索栏布局
    QHBoxLayout * searchLayout= new QHBoxLayout(searchLine);
    searchLayout->setSpacing(0);
    searchLayout->addStretch();
    searchLayout->addWidget(searchBtn);
    QHBoxLayout *hLayout=new QHBoxLayout();
    hLayout->addStretch();
    hLayout->addWidget(searchLine);
    hLayout->addStretch();

    tableWidget=new QTableWidget(10,2);
    tableWidget->setMinimumWidth(610);
    tableWidget->setMinimumHeight(500);
    tableWidget->setColumnWidth(0,300);
    tableWidget->setColumnWidth(1,290);
    tableWidget->setAcceptDrops(false);
    tableWidget->verticalHeader()->setHidden(true);
    QTableWidgetItem *headerTitle=new QTableWidgetItem("Title");
    QTableWidgetItem *headerUrl=new QTableWidgetItem("url");
    tableWidget->setHorizontalHeaderItem(0,headerTitle);
    tableWidget->setHorizontalHeaderItem(1,headerUrl);
    tableWidget->horizontalHeader()->setFixedHeight(30);
    tableWidget->verticalHeader()->resizeSections(QHeaderView::Stretch);
//    QPalette palette1;
//    palette1.setColor(QPalette::Base,QColor(7,7,7));
    tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section {font: 75 20pt ;background-color:lightblue;color: black;padding-left: 4px;border: 1px solid #6c6c6c;}");
    tableWidget->horizontalHeader()->setFont(QFont("幼圆",12,100));
    tableWidget->setAutoFillBackground(true);
//    tableWidget->setPalette(palette1);
    tableWidget->setCursor(QCursor(Qt::ArrowCursor));
    tableWidget->horizontalScrollBar()->setStyleSheet("QScrollBar:horizontal {"
                                                      "background: rgb(7,7,7);"
                                                      "height: 10px;"
                                                      "margin: 0px 0px 0px 0px;"
                                                  "}"
                                                  "QScrollBar::handle:horizontal {"
                                                      "background: rgb(27, 27, 28);"
                                                      "min-width: 20px;"
                                                      "margin: 2px 0px 1px 0px;"
                                                      "border-radius: 3px;"
                                                      "border: none;"
                                                  "}"
                                                  "QScrollBar::handle:hover:horizontal {"
                                                      "background: rgb(47, 47, 47);"
                                                      "min-width: 20px;"
                                                      "margin: 2px 0px 1px 0px;"
                                                      "border-radius: 3px;"
                                                      "border: none;"
                                                  "}"
                                                  "QScrollBar::handle:pressed:horizontal {"
                                                      "background: rgb(27, 27, 27);"
                                                      "min-width: 20px;"
                                                      "margin: 2px 0px 1px 0px;"
                                                      "border-radius: 3px;"
                                                      "border: none;"
                                                  "}"
                                                  "QScrollBar::add-line:horizontal {"
                                                      "border: 0px solid grey;"
                                                      "background: rgb(255,0,0);"
                                                      "width: 0px;"
                                                      "subcontrol-position: right;"
                                                      "subcontrol-origin: margin;"
                                                  "}"

                                                  "QScrollBar::sub-line:horizontal {"
                                                      "border: 0px solid grey;"
                                                      "background: #32CC99;"
                                                      "width: 0px;"
                                                      "subcontrol-position: left;"
                                                      "subcontrol-origin: margin;"
                                                  "}"

                                                  "QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal {"
                                                      "background: none;"
                                                  "};");
    tableWidget->verticalScrollBar()->setStyleSheet("QScrollBar:vertical {"
                                                    "background: transparent;"
                                                        "width:  10px;"
                                                        "margin: 22px 0px 22px 0px;"
                                                    "}"

                                                   " QScrollBar::handle:vertical {"
                                                       " border: 0px solid #3d7bad;"
                                                        "background-color:rgb(27,27,28);"
                                                        "border-radius: 3px;"
                                                        "min-height: 5px;"
                                                        "margin: 0px -1px 0 -0.5px;"
                                                    "}"

                                                    "QScrollBar::handle:hover{"
                                                    "background: rgb(47, 47, 47);"
                                                    "min-height: 20px;"
                                                    "margin: 0px -1px 0px -0.5px;"
                                                    "border-radius: 3px;"
                                                    "border: none;"
                                                       "}"
                                                    "QScrollBar::handle:pressed{"
                                                          "background-color:rgb(47,47,47);"
                                                       "}"
                                                    "QScrollBar::add-line:vertical {"
                                                    "subcontrol-origin: margin;"
                                                    " border: 0px solid green;"
                                                    " height: 20px;"
                                                        "subcontrol-position: bottom;"
                                                      "  subcontrol-origin: margin;"
                                                   "}"

                                                   " QScrollBar::sub-line:vertical {"
                                                    "subcontrol-origin: margin;"
                                                    " border: 0px solid red;"
                                                    " height: 20px;"
                                                        "subcontrol-position: top;"
                                                      "  subcontrol-origin: margin;"
                                                    "}"

                                                    "QScrollBar::up-arrow:vertical{"
                                                          "border: 0px solid rgb(255,0,0);"
                                                          "background-image :url(:/project/picup);"
                                                          "background-color:rgb(17,17,17);"
                                                          "width: 17px;"
                                                         " height: 17px;"
                                                         " margin: 1px 2px 1px 4px;"
                                                          /*background: none;*/
                                                      "}"
                                                      "QScrollBar::down-arrow:vertical {"
                                                           "border: 0px solid #CD00CD;"
                                                           "width: 17px;"
                                                           "height: 17px;"
                                                          " background-image :url(:/project/picdown);"
                                                          " margin: 1px 2px 1px 3px;"
                                                           /*background: none;*/
                                                    "}"
                                                "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {"
                                                    "background: none;"
                                                "};");


    QHBoxLayout *tableLayout=new QHBoxLayout();
    tableLayout->addStretch();
    tableLayout->addWidget(tableWidget);
    tableLayout->addStretch();
    //总体布局
    QVBoxLayout *mainLayout=new QVBoxLayout(this);
    mainLayout->addSpacing(50);
    mainLayout->addLayout(hLayout);
    mainLayout->addSpacing(50);
    mainLayout->addLayout(tableLayout);
    mainLayout->addStretch();
    setLayout(mainLayout);

    connect(searchBtn,SIGNAL(clicked()),this,SLOT(startSearch()));
    connect(searchLine,SIGNAL(returnPressed()),this,SLOT(startSearch()));
    connect(tableWidget,SIGNAL(cellDoubleClicked(int,int)),SLOT(doubleClick(int,int)));

}
void SearchWidget::startSearch(){
    qDebug()<<"startSearch";
       QString keyword = searchLine->text();
       QString web[3]={"http://so.iqiyi.com/so/q_","http://www.soku.com/search_video/q_",
                      "http://www.soku.com/t/nisearch/"};
       //urls.append("http://www.scut.edu.cn/");

       tableWidget->clearContents();
       int pc=0;
       int co=0;
       while(++pc<=3){
       dealWeb::urls->clear();
       dealWeb::urls->append(web[pc-1]+keyword);

        int count=1;
       if(keyword.length() != 0)
       {
           while(count<=2)
           {
               QString* a=matchKeywords(keyword);

               qDebug()<<a[0];
               qDebug()<<a[1];
               if(a[0].compare("null")!=0)
               {
                   qDebug()<<"add item";
                   tableWidget->setItem(co,0,new QTableWidgetItem(a[0]));
                   tableWidget->setItem(co,1,new QTableWidgetItem(a[1]));
                   count++;
                   co++;
               }
           }


       }
       else
       {
           QMessageBox::information(this, tr("ERROR") , tr("请输入关键字 !!!!") );
       }
       }
}
void SearchWidget::doubleClick(int row,int column){
    if(column==1)
        {
            QTableWidgetItem *item=tableWidget->item(row,column);
            QString url=item->text();
            emit openWebVideo(url);
        }
}
