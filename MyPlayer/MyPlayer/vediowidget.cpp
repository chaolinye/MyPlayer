#include "vediowidget.h"
#include <QColor>
#include <QFileDialog>
#include <QDebug>
#include <QThread>
#include <QPalette>
#include <QPixmap>
#include "controlwidget.h"
#include <QSound>

bool VedioWidget::isPlay=false;
bool VedioWidget::isPause=false;
bool VedioWidget::isStop=true;
VedioWidget::VedioWidget(QWidget *parent) :
    QWidget(parent)
{
    /*设置播放窗口背景*/
    setAutoFillBackground(true);
    QPalette p=this->palette();
    p.setBrush(QPalette::Window,QColor(7,7,7));

    this->setPalette(p);

    isMute=false;

    init();
    resize(800,400);

}
void VedioWidget::init()
{
    /*初始化视频引擎*/
    vlcObject=libvlc_new (0, NULL);
}

void VedioWidget::startVedio(QString fileOpen) {
    qDebug()<<"Open a video";
    /*判断无效的文件类型*/
    if(fileOpen==NULL||fileOpen==""||fileOpen=="~")
        return;
    qDebug()<<"file is available";
    /*判断当前是否正在播放视频,如果是,则终止播放当前视频*/
    if(!isStop)
        stop();
//    if(vlcPlayer==NULL&&vlcPlayer&& libvlc_media_player_is_playing(vlcPlayer) ){
//        qDebug()<<"停止当前视频的播放";
//        stop();
//    }
    qDebug()<<"xxxxxxxxxxxS";
    /* 新建一个视频对象 */
    vlcMedia = libvlc_media_new_path(vlcObject,fileOpen.toStdString().data());
//     vlcMedia = libvlc_media_new_path(vlcObject,fileOpen.toUtf8());
    qDebug()<<"new video Object";
    if( !vlcMedia )
        return;
    /* 解析媒体实例 */
    libvlc_media_parse(vlcMedia);

    /* 获取媒体文件的播放长度,  返回 ms */
    sumTime=libvlc_media_get_duration(vlcMedia);
    qDebug()<<"总时间："<<sumTime;

    emit setSumTime(sumTime);


    /* 创建一个VLC播放器  */
    vlcPlayer = libvlc_media_player_new_from_media (vlcMedia);
    libvlc_media_release(vlcMedia);

    /* 集成播放器于不同系统的窗口部件中 */
#if defined(Q_OS_MAC)
    libvlc_media_player_set_nsobject(vlcPlayer, (void*)videoWidget->winId());
#elif defined(Q_OS_UNIX)
    libvlc_media_player_set_xwindow(vlcPlayer, (void*)videoWidget->winId());
#elif defined(Q_OS_LINUX)
    libvlc_media_player_set_xwindow(vlcPlayer, (void*)videoWidget->winId());
#elif defined(Q_OS_WIN)
    libvlc_media_player_set_hwnd(vlcPlayer, (void*)this->winId());
#endif

    /* 播放视频 */
    libvlc_media_player_play (vlcPlayer);
    qDebug()<<"xxxxxxxxxxxS";

    qDebug()<<"开始播放视频";
    emit fileName(fileOpen);
    isPlay=true;
    isPause=false;
    isStop=false;
//    /*发出视频开始播放的信号*/
    emit startPlay(true);
}
void VedioWidget::stopVedio()
{
   stop();
}
void VedioWidget::stop()
{

//    if(!vlcMedia)
//        return;
    if(!vlcPlayer)
        return;
    if(isStop){
        return;
    }
    /* 停止播放 */
    if(libvlc_media_player_is_playing(vlcPlayer)){
        qDebug()<<"stop video";
        libvlc_media_player_stop (vlcPlayer);
    }

    libvlc_media_player_release(vlcPlayer);

    /* 释放media_player */
//    libvlc_media_release(vlcMedia);
//    vlcMedia=NULL;
//    qDebug()<<(vlcMedia==NULL);
//    vlcPlayer=NULL;
//    libvlc_release (vlcObject);
    qDebug()<<"视频停止播放,发出视频不在播放信号";
    isPlay=false;
    isPause=false;
    isStop=true;
}
void VedioWidget::pauseVedio()
{
    if(isStop){
        return;
    }
    if( vlcMedia==NULL )
        return;
    libvlc_media_player_pause(vlcPlayer);
    isPause=true;
    isPlay=false;
    isStop=false;
}
void VedioWidget::resumeVedio()
{
    if(isStop){
        return;
    }
    if(!vlcMedia)
        return;
    libvlc_media_player_set_pause(vlcPlayer,0);
    isPause=false;
    isPlay=true;
    isStop=false;

}
void VedioWidget::setVolume(int volume){
    if(isStop){
        return;
    }
    if(!vlcPlayer)
        return;
    libvlc_audio_set_volume(vlcPlayer,volume);
    qDebug()<<"音量："<<volume;
}

void VedioWidget::setTime(int time)
{
    QSound::play(":/sounds/press.wav");
    if(isStop==true)
        return;
    qDebug()<<"当前时间"<<time;
    libvlc_media_player_set_time(vlcPlayer,time*1000);
}
void VedioWidget::vedioChangeSize()
{
    qDebug()<<"视频窗口大小变化";
}
void VedioWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    QPalette pal(palette());
    pal.setBrush(QPalette::Window,
    QBrush(m_image.scaled(event->size(), Qt::IgnoreAspectRatio,
    Qt::SmoothTransformation)));
    setPalette(pal);
}
void VedioWidget::mouseDoubleClickEvent(QMouseEvent *){
    emit fullScreen();
}
