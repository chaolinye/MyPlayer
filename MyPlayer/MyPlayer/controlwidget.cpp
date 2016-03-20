#include "controlwidget.h"
#include <QDebug>
#include <QPixmap>
#include <QImage>
#include <QBitmap>
#include <QPalette>
#include <QColor>
#include <QRgb>
#include <QDebug>
#include <QSound>



ControlWidget::ControlWidget(QWidget *parent) :
    QWidget(parent)
{
    init();
    isMute=false;
    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timing()));


}

void ControlWidget::init(){
    //设置控制面板
    this->setAutoFillBackground(true);
    QPalette p=this->palette();
    p.setColor(QPalette::Window,QColor(7, 7, 7,255));
    this->setPalette(p);

    //初始化视频进度Slider
    slider=new SliderForVideo(Qt::Horizontal);
    //设置音量Slider
    volumeSlider=new QSlider();
    volumeSlider->setOrientation(Qt::Horizontal);
    volumeSlider->setFixedSize(95,20);
    volumeSlider->setValue(80);
    volumeSlider->setStyleSheet(
                    "QToolTip {border: 2px solid rgb(43,43,45);color:white;background-color: rgb(27,27,28);padding: 3px; border-radius: 3px;opacity: 200;}"
                    "QSlider::groove:horizontal {                                "
                    "     border: 1px   solid #999999;                           "
                    "     height: 1px;                                           "
                    "     margin: 0px 0py;                                       "
                    "     left: 9px; right: 9px;                                 "
                    " }                                                          "
                    "QSlider::handle:horizontal {                                "
                    "     border: 1px solid #5c5c5c;                             "
                    " border-image:url(:/images/handle06.png);                         "
                    "     width: 20px;                                           "
                    "     margin: -11px -11px -11px -11px;                       "
                    " }                                                          "
                    "QSlider::handle:hover:horizontal{                           "
                    "     border: 1px solid #5c5c5c;                             "
                    " border-image:url(:/images/handle02.png);                         "
                    "     width: 20px;                                           "
                    "     margin: -11px -11px -11px -11px;                       "
                    "}                                                           "
                    "QSlider::handle:pressed:horizontal{                         "
                    "     border: 1px solid #5c5c5c;                             "
                    " border-image:url(:/images/handle01.png);                         "
                    "     width: 20px;                                           "
                    "     margin: -11px -11px -11px -11px;                       "
                    "}                                                           "
                    "                                                            "
                    "QSlider::sub-page:horizontal{                               "
                    " background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(11, 119, 225, 255), stop:0.65 rgba(11,119, 225, 255), stop:1 rgba(92, 184, 254, 255));                      "
                    "}                                                           "
                    "QSlider::add-page:horizontal{                               "
                    " background: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:1, stop:0 rgba(53,53,53, 255));  "
                    "}"
                    );

    //设置播放按钮
    startBtn=new QPushButton();
    startBtn->setCursor(Qt::PointingHandCursor);
    startBtn->setFixedSize(48,48);
    startBtn->setAutoFillBackground(true);
    startBtn->setIconSize(QSize(48, 48));
    startBtn->setStyleSheet("QPushButton{border-image: url(:/images/playBtn01);}"
                            "QPushButton:hover{border-image: url(:/images/playBtn02);}"
                            "QPushButton:pressed{border-image: url(:/images/playBtn03);}");

    //设置时间label
    timeLabel=new QLabel(this);
    timeLabel->setAutoFillBackground(true);
    timeLabel->setPalette(QPalette(QPalette::Background,QColor(7,7,7)));
//    timeLabel->setFixedSize(130,13);
    timeLabel->setFixedHeight(13);
    timeLabel->setFont(QFont("微软雅黑" ,10,10));
    //设置快进按钮
    fastBtn=new QPushButton(this);
    fastBtn->setCursor(Qt::PointingHandCursor);
    fastBtn->setFixedSize(17,13);
    fastBtn->setStyleSheet("QPushButton{border-image:url(:/images/fastBtn01);}"
                                 "QPushButton:hover{border-image:url(:/images/fastBtn02);}"
                                 "QPushButton:pressed{border-image:url(:/images/fastBtn03);}");
    //设置后退按钮
    rewindBtn=new QPushButton(this);
    rewindBtn->setCursor(Qt::PointingHandCursor);
    rewindBtn->setFixedSize(17,13);
    rewindBtn->setStyleSheet("QPushButton{border-image:url(:/images/rewindBtn01);}"
                             "QPushButton:hover{border-image:url(:/images/rewindBtn02);}"
                             "QPushButton:pressed{border-image:url(:/images/rewindBtn03);}");
    //设置停止按钮
    stopBtn=new QPushButton();
    stopBtn->setCursor(Qt::PointingHandCursor);
    stopBtn->setFixedSize(40,40);
    stopBtn->setAutoFillBackground(true);
    stopBtn->setIconSize(QSize(40, 40));
    stopBtn->setStyleSheet("QPushButton{border-image: url(:/images/stopBtn01.png);}"
                           "QPushButton:hover{border-image: url(:/images/stopBtn02.png);}"
                           "QPushButton:pressed{border-image: url(:/images/stopBtn03.png);}");
    //设置静音按钮
    muteBtn=new QPushButton();
    muteBtn->setCursor(Qt::PointingHandCursor);
    muteBtn->setAutoFillBackground(true);
    muteBtn->setFixedSize(16, 16);
    muteBtn->setStyleSheet("QPushButton{border-image: url(:/images/muteBtn02);}"
                           "QPushButton:hover{border-image: url(:/images/muteBtn01);}"
                           "QPushButton:pressed{border-image: url(:/images/muteBtn03);}");
    //设置下一个按钮
    nextBtn=new QPushButton();
    nextBtn->setCursor(Qt::PointingHandCursor);
    nextBtn->setFixedSize(40,40);
    nextBtn->setAutoFillBackground(true);
    nextBtn->setIconSize(QSize(40, 40));
    nextBtn->setStyleSheet("QPushButton{border-image: url(:/images/nextBtn01);}"
                           "QPushButton:hover{border-image: url(:/images/nextBtn02);}"
                           "QPushButton:pressed{border-image: url(:/images/nextBtn03);}");
    //设置上一个按钮
    preBtn=new QPushButton(this);
    preBtn->setCursor(Qt::PointingHandCursor);
    preBtn->setAutoFillBackground(true);
    preBtn->setFixedSize(40,40);
    preBtn->setIconSize(QSize(40, 40));
    preBtn->setStyleSheet("QPushButton{border-image: url(:/images/lastBtn01);}"
                          "QPushButton:hover{border-image: url(:/images/lastBtn02);}"
                          "QPushButton:pressed{border-image: url(:/images/lastBtn03);}");
    //设置打开文件按钮
    openFileBtn=new QPushButton(this);
    openFileBtn->setCursor(Qt::PointingHandCursor);
    openFileBtn->setFixedSize(20,20);
    openFileBtn->setStyleSheet("QPushButton{border-image:url(:/images/openFileBtn01);}"
                                    "QPushButton:hover{border-image:url(:/images/openFileBtn02);}"
                                    "QPushButton:pressed{border-image:url(:/images/openFileBtn03);}");
    //设置全屏按钮
    fullScreenBtn=new QPushButton(this);
    fullScreenBtn->setCursor(Qt::PointingHandCursor);
    fullScreenBtn->setFixedSize(24,18);
    fullScreenBtn->setStyleSheet("QPushButton{border-image:url(:/images/fullScreenBtn01);}"
                                 "QPushButton:hover{border-image:url(:/images/fullScreenBtn02);}"
                                 "QPushButton:pressed{border-image:url(:/images/fullScreenBtn03);}");
    //设置显示/隐藏列表按钮
    showListBtn=new QPushButton(this);
    showListBtn->setCursor(Qt::PointingHandCursor);
    showListBtn->setFixedSize(18,18);
    showListBtn->setStyleSheet("QPushButton{border-image:url(:/images/showListBtn04);}"
                               "QPushButton:hover{border-image:url(:/images/showListBtn05);}"
                               "QPushButton:pressed{border-image:url(:/images/showListBtn06);}");
    /*连接按钮的点击事件和相关的发射信号的函数*/
    connect(startBtn,SIGNAL(clicked()),this,SLOT(startVedio()));
    connect(stopBtn,SIGNAL(clicked()),this,SLOT(stopVedio()));
    connect(muteBtn,SIGNAL(clicked()),this,SLOT(quiet()));
    connect(fastBtn,SIGNAL(clicked()),this,SLOT(sendFast()));
    connect(rewindBtn,SIGNAL(clicked()),this,SLOT(sendRewind()));

    //设置面板布局
    mainLayout=new QVBoxLayout(this);
    btnLayout=new QHBoxLayout(this);
    sliderLayout=new QHBoxLayout(this);
    layout01=new QVBoxLayout(this);
    layout01->setSpacing(0);
    layout01->addWidget(timeLabel);
    layout01->addWidget(showListBtn);
    btnLayout->setMargin(0);
    btnLayout->setSpacing(0);
    btnLayout->setContentsMargins(0,0,0,0);
    btnLayout->addSpacing(10);
    btnLayout->addLayout(layout01);
    btnLayout->addStretch();
    btnLayout->addStretch();
    btnLayout->addSpacing(68);
    btnLayout->addWidget(preBtn);
    btnLayout->addWidget(startBtn);
    btnLayout->addWidget(nextBtn);
    btnLayout->addWidget(stopBtn);
    btnLayout->addSpacing(30);
    btnLayout->addWidget(muteBtn);
    btnLayout->addWidget(volumeSlider);
    btnLayout->addStretch();
    btnLayout->addStretch();
    btnLayout->addWidget(openFileBtn);
    btnLayout->addWidget(fullScreenBtn);
    btnLayout->addSpacing(5);
    sliderLayout->setSpacing(0);
    sliderLayout->addWidget(rewindBtn);
    sliderLayout->addWidget(slider);
    sliderLayout->addWidget(fastBtn);
    mainLayout->addLayout(sliderLayout);
    mainLayout->addLayout(btnLayout);
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
    setLayout(mainLayout);

}
/*点击播放按钮触发的函数*/
void ControlWidget::startVedio()
{
    QSound::play(":/sounds/press.wav");
    if(VedioWidget::isStop==true)
        return;
    if(VedioWidget::isPause)
    {

        startBtn->setStyleSheet("QPushButton{border-image: url(:/images/playBtn01);}"
                                "QPushButton:hover{border-image: url(:/images/playBtn02);}"
                                "QPushButton:pressed{border-image: url(:/images/playBtn03);}");
        timer->start(1000);
        emit play();
    }
    else{
        startBtn->setStyleSheet("QPushButton{border-image: url(:/images/pauseBtn01);}"
                                "QPushButton:hover{border-image: url(:/images/pauseBtn02);}"
                                "QPushButton:pressed{border-image: url(:/images/pauseBtn03);}");
        timer->stop();
        emit pause();
    }
}
/*点击停止按钮触发的函数*/
void ControlWidget::stopVedio()
{
    QSound::play(":/sounds/press.wav");
    if(VedioWidget::isStop==true)
        return;
    emit stop();
    startBtn->setStyleSheet("QPushButton{border-image: url(:/images/playBtn01);}"
                            "QPushButton:hover{border-image: url(:/images/playBtn02);}"
                            "QPushButton:pressed{border-image: url(:/images/playBtn03);}");
    timer->stop();
    slider->setValue(0);
    timeLabel->setText("");
}
/*点击静音按钮触发的函数*/
void ControlWidget::quiet(){
    QSound::play(":/sounds/press.wav");
    if(!isMute)
    {
        muteBtn->setStyleSheet("QPushButton{border-image: url(:/images/muteBtn04);}"
                               "QPushButton:hover{border-image: url(:/images/muteBtn05);}"
                               "QPushButton:pressed{border-image: url(:/images/muteBtn06);}");
        isMute=true;
        qDebug()<<"发出静音信号";
        emit currentVolume(0);
    }
    else{
        muteBtn->setStyleSheet("QPushButton{border-image: url(:/images/muteBtn02);}"
                               "QPushButton:hover{border-image: url(:/images/muteBtn01);}"
                               "QPushButton:pressed{border-image: url(:/images/muteBtn03);}");
        isMute=false;
        qDebug()<<"取消静音信号";
        currentVolume(volumeSlider->value());
    }
}
/*设置进度条*/
void ControlWidget::setTimeSliderLong(int time){
    qDebug()<<"time:"<<time;
    slider->setMaximum(time/1000);
    currentTimeString=timeForString(0);
    totalTimeString=timeForString(time/1000);
    updateTimeLabel();
    timer->start(1000);
}
/*设置进度条的渐进*/
void ControlWidget::timing()
{
    slider->setValue(slider->value()+1);
    currentTimeString=timeForString(slider->value());
    updateTimeLabel();
}
/*点击快进按钮触发的事件*/
void ControlWidget::sendFast()
{
    if(VedioWidget::isStop==true)
        return;
    qDebug()<<"fastfast";
    emit fast(slider->value()+5);
    slider->setValue(slider->value()+5);
}
/*点击后退按钮触发的事件*/
void ControlWidget::sendRewind()
{
    if(VedioWidget::isStop==true)
        return;
    emit rewind(slider->value()-5);
    slider->setValue(slider->value()-5);

}
/*根据视频面板的信号触发的函数*/
void ControlWidget::setWidgetState(bool b){
    qDebug()<<"控制面板感应到视频开始播放";
    slider->setValue(0);
    emit currentVolume(volumeSlider->value());
}
QString ControlWidget::timeForString(int time){
    s=time%60;
    m=(time/60)%60;
    h=time/60/60;

    sstream.str("");
    sstream<<s;
    s_s=sstream.str();
    sstream.str("");
    sstream<<m;
    s_m=sstream.str();
    sstream.str("");
    sstream<<h;
    s_h=sstream.str();
    if(s<10){
        s_s="0"+s_s;
    }
    if(m<10){
        s_m="0"+s_m;
    }
    if(h<10){
        s_h="0"+s_h;
    }
    return QString::fromStdString(s_h)+QString::fromStdString(":")+QString::fromStdString(s_m)+QString::fromStdString(":")+QString::fromStdString(s_s);
}
void ControlWidget::updateTimeLabel(){
    timeLabel->setText(currentTimeString+"/"+totalTimeString);
}
