#ifndef VEDIOWIDGET_H
#define VEDIOWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <libvlc_structures.h>
#include <libvlc.h>
#include <libvlc_media.h>
#include <libvlc_media_player.h>
#include <libvlc_media_list.h>
#include <libvlc_media_list_player.h>
#include <libvlc_media_library.h>
#include <libvlc_media_discoverer.h>
#include <libvlc_events.h>
#include <libvlc_vlm.h>
#include <deprecated.h>
#include <vlc.h>
#include <QPixmap>
#include <QResizeEvent>
#include <QMouseEvent>


/*
 * 视频播放窗口类,实现视频的播放以及其他功能
*/

class VedioWidget : public QWidget
{
    Q_OBJECT
public:
    explicit VedioWidget(QWidget *parent = 0);
    static bool isPlay;
    static bool isPause;
    static bool isStop;
    /*终止视频播放*/
    void stop();

signals:
    void setSumTime(int time);
    void startPlay(bool b);
    void fileName(QString);
    void fullScreen();

protected:
    void resizeEvent(QResizeEvent *event);
    void mouseDoubleClickEvent(QMouseEvent * event);
    /*槽函数*/
public slots:
    /*开始视频*/
    void startVedio(QString fileOpen);
    /*终止视频*/
    void stopVedio();
    /*暂停视频*/
    void pauseVedio();
    /*恢复视频播放*/
    void resumeVedio();
    /*设置音量*/
    void setVolume(int volume);
    /*设置进度*/
    void setTime(int time);
    /*视频窗口改变大小*/
    void vedioChangeSize();
//    /*设置全屏*/
//    void setFullScreen(bool);

private:
//    QVBoxLayout *mainLayout;
//    QWidget *vedioWidget;
    QPixmap m_image;

    /*vlc引擎类*/
    libvlc_instance_t * vlcObject;
    /*vlc播放主体类*/
    libvlc_media_player_t *vlcPlayer;
    /*vlc视频对象类*/
    libvlc_media_t *vlcMedia;

    /*音量，0——100*/
    int volume;
    /*静音状态*/
    bool isMute;
    /*视频总时长*/
    libvlc_time_t sumTime;
    /*视频当前时长*/
    libvlc_time_t currentTime;

    //初始化界面布局
    void init();





};

#endif // VEDIOWIDGET_H
