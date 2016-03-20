#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QContextMenuEvent>
#include <QAction>
#include <QMenu>
#include "vediowidget.h"
#include "controlwidget.h"
#include "browserwidget.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QWidget>
#include "mylistwidget.h"
#include "titlebar.h"
#include <QStackedWidget>
#include<QScrollBar>
#include <QDropEvent>
#include "searchwidget.h"

/*
    这是视频播放器的主窗口类，包含主体的布局，连接不同widget之间信号和槽

*/
/* 使用三个常量标注播放、搜索、浏览器选项卡 */
const int VIDEOSTATE=1;
const int SEARCHSTATE=2;
const int BROWSERSTATE=3;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //当前的状态是否是最大化，主要给TitleBar判断最大化按钮图片使用
    static bool isMax;
signals:
    //要求播放视频的信号
    void startLocalVedio(QString);
    //要求改变选项卡的信号
    void changeState(int);

    void searchWebVedio(QString);
protected:
    /* 重写右键事件 */
    void contextMenuEvent(QContextMenuEvent *);
    /* 重写拖放事件 */
    void dropEvent(QDropEvent *);
    void dragEnterEvent(QDragEnterEvent *);
    /* 重写改变事件 */
    void changeEvent(QEvent *);
protected slots:
    /*打开文件*/
    void openFile();
    /* 进入播放器选项卡 */
    void setVideoState();
    /* 进入搜索页面选项卡 */
    void setSearchState();
    /* 进入浏览器选项卡*/
    void setBrowserState();
    /* 切换播放列表 */
    void changeList();
    /*显示或隐藏播放列表*/
    void showOrHideList();
    /*全屏或退出全屏*/
    void setFullScreen();
    /* 上一个视频 */
    void preVideo();
    /* 下一个视频 */
    void nextVideo();
    /* 播放启动音效*/
    void playSound();
    /* 搜索视频 */
    void searchVideo();
private:
    //网格布局
    QGridLayout *layout;
    //水平布局
    QHBoxLayout *layout2;
    //垂直布局
    QVBoxLayout *layout3;

    //堆栈窗体
    QStackedWidget *stack;
    //播放选项窗口
    QWidget *playerWidget;
    //浏览器选项窗口
    BrowserWidget *browser;
    //搜索选项窗口
    SearchWidget *searchWidget;

    //MainWindow的中心Widget
    QWidget *localWidget;

    //视频播放窗口
    VedioWidget *vedioWidget;
    //视频控制面板
    ControlWidget *controlWidget;

    //视频播放列表
    QLineEdit *searchLine;
    QPushButton *searchBtn;
    QPushButton *playerListBtn;
    QPushButton *onlineListBtn;
    MyListWidget *myListWidget;
    QListWidget *onlineListWidget;
    QVBoxLayout *listLayout;

    //自定义标题栏
    TitleBar *titleBar;

    //初始化界面布局
    void init();
    //布局列表栏
    void createListWidget();
    //记录当前的选项卡
    int tabState;
    //列表是否隐藏
    bool isListHide;

};

#endif // MAINWINDOW_H
