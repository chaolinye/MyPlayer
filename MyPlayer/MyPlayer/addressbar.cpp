#include "addressbar.h"

AddressBar::AddressBar(QWidget *parent) :
    QWidget(parent)
{
   homeBtn=new QPushButton(this);
   backBtn=new QPushButton(this);
   forwardBtn=new QPushButton(this);
   refreshBtn=new QPushButton(this);
   homeBtn->setFixedSize(24,24);
   backBtn->setFixedSize(24,24);
   forwardBtn->setFixedSize(24,24);
   refreshBtn->setFixedSize(24,24);

   homeBtn->setStyleSheet("QPushButton{border-image: url(:/images/homeBtn03);}"
                              "QPushButton:hover{border-image: url(:/images/homeBtn01);}"
                              "QPushButton:pressed{border-image: url(:/images/homeBtn02);}");
   homeBtn->setToolTip("主页");

   backBtn->setStyleSheet("QPushButton{border-image: url(:/images/backBtn02);}"
                          "QPushButton:hover{border-image: url(:/images/backBtn01);}"
                          "QPushButton:pressed{border-image: url(:/images/backBtn03);}");
   backBtn->setToolTip("返回");

   forwardBtn->setStyleSheet("QPushButton{border-image: url(:/images/forwardBtn02);}"
                             "QPushButton:hover{border-image: url(:/images/forwardBtn01);}"
                             "QPushButton:pressed{border-image: url(:/pimages/forwardBtn03);}");
   forwardBtn->setToolTip("前进");

   refreshBtn->setStyleSheet("QPushButton{border-image: url(:/images/refreshBtn01);}"
                             "QPushButton:hover{border-image: url(:/images/refreshBtn03);}"
                             "QPushButton:pressed{border-image: url(:/images/refreshBtn02);}");
   refreshBtn->setToolTip("刷新");

   addressEdit = new QLineEdit(this);
   QHBoxLayout *layout1 = new QHBoxLayout(this);

   this->setLayout(layout1);
   layout1->addWidget(homeBtn);
   layout1->addWidget(backBtn);
   layout1->addWidget(forwardBtn);
   layout1->addWidget(refreshBtn);
   layout1->addWidget(addressEdit);
}
