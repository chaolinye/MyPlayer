#ifndef CONTROLWIDGET_H
#define CONTROLWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QSlider>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QTimer>
#include <SliderForVideo.h>
#include "vediowidget.h"
#include <sstream>
#include <string>
using namespace std;

/*
 *
 * 视频控制面板类，用于控制视频播放的相关功能
*/

class ControlWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ControlWidget(QWidget *parent = 0);
    /*视频进度条*/
    SliderForVideo *slider;
    /*音量进度条*/
    QSlider *volumeSlider;
    /*全屏按钮*/
    QPushButton *fullScreenBtn;
    /*打开文件按钮*/
    QPushButton *openFileBtn;
    /*显示/隐藏list的按钮*/
    QPushButton *showListBtn;
    /*下一条按钮*/
    QPushButton *nextBtn;
    /*上一条按钮*/
    QPushButton *preBtn;

signals:
    /*播放视频信号*/
    void play();
    /*暂停视频信号*/
    void pause();
    /*停止视频信号*/
    void stop();
    /*快进*/
    void fast(int time);
    /*后退*/
    void rewind(int time);
    /*当前音量*/
    void currentVolume(int time);


public slots:
    /*发出播放视频信号或暂停视频信号*/
    void startVedio();
    /*发出停止视频信号*/
    void stopVedio();
    /*发出静音信号*/
    void quiet();
    /*设置进度条时长*/
    void setTimeSliderLong(int time);
    /*进度条前进*/
    void timing();
    /*发出快进信号*/
    void sendFast();
    /*发出后退信号*/
    void sendRewind();
    /*设置组件状态*/
    void setWidgetState(bool b);

private:

    /*播放和暂停按钮*/
    QPushButton *startBtn;
    /*快进按钮*/
    QPushButton *fastBtn;
    /*后退按钮*/
    QPushButton *rewindBtn;
    /*静音按钮*/
    QPushButton *muteBtn;
    /*停止按钮*/
    QPushButton *stopBtn;

    /*时间label*/
    QLabel *timeLabel;


    /*视频控制面板主布局*/
    QVBoxLayout *mainLayout;
    /*按钮布局*/
    QHBoxLayout *btnLayout;
    /*进度条布局*/
    QHBoxLayout *sliderLayout;
    QVBoxLayout *layout01;
    /*计时器*/
    QTimer *timer;
    /*记录静音的状态*/
    bool isMute;

    /*初始化界面*/
    void init();

    QString timeForString(int);
    QString currentTimeString;
    QString totalTimeString;
    stringstream sstream;
    int s;
    int m;
    int h;
    string s_s;
    string s_m;
    string s_h;
    void updateTimeLabel();
};

#endif // CONTROLWIDGET_H
