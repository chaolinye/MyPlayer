#include "mainwindow.h"
#include <QFileDialog>
#include <QMenuBar>
#include <QBitmap>
#include <QPixmap>
#include <QHBoxLayout>
#include <QPropertyAnimation>
#include <QSound>
//初始化最大化为假
bool MainWindow::isMax=false;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    /*设置主窗口状态*/
    setWindowTitle("MyPlayer");
    setAcceptDrops(true);
    setFocus();
    setGeometry(150,30,1058, 656);
    setWindowFlags(Qt::FramelessWindowHint);
    menuBar()->hide();
    this->setAutoFillBackground(true);
    QPalette p=this->palette();
    p.setBrush(QPalette::Window,QColor(7,7,7));
    this->setPalette(p);
    //初始化界面布局
    init();
    //电影弹,是程序由透明渐变为实体
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(2000);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
  //  connect(animation,SIGNAL(finished()),this,SLOT(playSound()));
}

/*初始化界面控件*/
void MainWindow::init()
{
    //初始化记录变量
    isListHide=false;
    tabState=VIDEOSTATE;
    //初始化各Widget
    vedioWidget=new VedioWidget(this);
    controlWidget=new ControlWidget(this);
    createListWidget();
    titleBar=new TitleBar(this);
    titleBar->setFixedHeight(40);

    /*连接视频控制面板和视频播放窗口的信号和槽*/
    connect(controlWidget,SIGNAL(play()),vedioWidget,SLOT(resumeVedio()));
    connect(controlWidget,SIGNAL(pause()),vedioWidget,SLOT(pauseVedio()));
    connect(controlWidget,SIGNAL(stop()),vedioWidget,SLOT(stopVedio()));
    connect(vedioWidget,SIGNAL(setSumTime(int)),controlWidget,SLOT(setTimeSliderLong(int)));
    connect(vedioWidget,SIGNAL(fullScreen()),this,SLOT(setFullScreen()));
    connect(controlWidget->slider,SIGNAL(sliderMoved(int)),vedioWidget,SLOT(setTime(int)));
    connect(controlWidget,SIGNAL(fast(int)),vedioWidget,SLOT(setTime(int)));
    connect(controlWidget,SIGNAL(rewind(int)),vedioWidget,SLOT(setTime(int)));
    connect(controlWidget->volumeSlider,SIGNAL(sliderMoved(int)),vedioWidget,SLOT(setVolume(int)));
    connect(controlWidget->volumeSlider,SIGNAL(valueChanged(int)),vedioWidget,SLOT(setVolume(int)));
    connect(controlWidget,SIGNAL(currentVolume(int)),vedioWidget,SLOT(setVolume(int)));
    connect(controlWidget->fullScreenBtn,SIGNAL(clicked()),this,SLOT(setFullScreen()));
    connect(controlWidget->openFileBtn,SIGNAL(clicked()),this,SLOT(openFile()));
    connect(controlWidget->showListBtn,SIGNAL(clicked()),this,SLOT(showOrHideList()));
    connect(controlWidget->preBtn,SIGNAL(clicked()),this,SLOT(preVideo()));
    connect(controlWidget->nextBtn,SIGNAL(clicked()),this,SLOT(nextVideo()));
    connect(vedioWidget,SIGNAL(startPlay(bool)),controlWidget,SLOT(setWidgetState(bool)));
    /* 连接主窗口和视频播放窗口的信号和槽*/
    connect(this,SIGNAL(startLocalVedio(QString)),vedioWidget,SLOT(startVedio(QString)));
    /* 连接列表和视频播放窗口的信号和槽*/
    connect(vedioWidget,SIGNAL(fileName(QString)),myListWidget,SLOT(addFile(QString)));
    connect(myListWidget,SIGNAL(sendFileName(QString)),vedioWidget,SLOT(startVedio(QString)));
    /* 连接自定义标题栏和主窗口的信号和槽*/
    connect(titleBar->openFileAction,SIGNAL(triggered()),this,SLOT(openFile()));
    connect(titleBar->exitAction,SIGNAL(triggered()),this,SLOT(close()));
    connect(titleBar->showVideoWidget,SIGNAL(clicked()),this,SLOT(setVideoState()));
    connect(titleBar->showBrowser,SIGNAL(clicked()),this,SLOT(setBrowserState()));
    connect(titleBar->showSearch,SIGNAL(clicked()),this,SLOT(setSearchState()));
    connect(titleBar,SIGNAL(signal_min()),this,SLOT(showMinimized()));
    connect(titleBar,SIGNAL(signal_close()),this,SLOT(close()));
    connect(titleBar,SIGNAL(signal_max()),this,SLOT(showMaximized()));
    connect(titleBar,SIGNAL(signal_restore()),this,SLOT(showNormal()));
    /* 连接自定义标题栏和视频播放窗口的信号和槽*/
    connect(titleBar,SIGNAL(signal_max()),vedioWidget,SLOT(vedioChangeSize()));
    connect(titleBar,SIGNAL(signal_restore()),vedioWidget,SLOT(vedioChangeSize()));

    //主窗口布局
    layout=new QGridLayout(this);
    layout->addWidget(vedioWidget,0,0,8,1);
    layout->addWidget(controlWidget,8,0,1,1);
    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);
    layout2=new QHBoxLayout(this);
    layout2->addLayout(listLayout);
    layout2->addLayout(layout);
    layout2->setSpacing(0);
    layout2->setContentsMargins(0,0,0,0);
    playerWidget=new QWidget();
    playerWidget->setLayout(layout2);
    searchWidget=new SearchWidget();
    browser=new BrowserWidget();
    stack=new QStackedWidget();
    stack->addWidget(playerWidget);
    stack->addWidget(searchWidget);
    stack->addWidget(browser);
    layout3=new QVBoxLayout(this);
    layout3->addWidget(titleBar);
    layout3->addWidget(stack);
    layout3->setSpacing(0);
    layout3->setContentsMargins(0,0,0,0);
    localWidget=new QWidget();
    localWidget->setLayout(layout3);
    setCentralWidget(localWidget);
    //连接改变选项卡的信号和槽
    connect(this,SIGNAL(changeState(int)),stack,SLOT(setCurrentIndex(int)));


    connect(searchWidget,SIGNAL(openWebVideo(QString)),browser,SLOT(loadWebPage(QString)));
    connect(searchWidget,SIGNAL(openWebVideo(QString)),this,SLOT(setBrowserState()));
    connect(this,SIGNAL(searchWebVedio(QString)),browser,SLOT(loadWebPage(QString)));
    connect(this,SIGNAL(searchWebVedio(QString)),this,SLOT(setBrowserState()));


}

/*初始化播放列表*/
void MainWindow::createListWidget(){
    //设置搜索栏
    QPalette palette1=this->palette();
    searchLine=new QLineEdit(this);
    searchLine->setMaximumWidth(241);
    searchLine->setMinimumHeight(28);
    searchLine->setTextMargins(0, 1, 32, 1);

    searchBtn=new QPushButton(searchLine);
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
    searchLine->setPlaceholderText("请输入要看视频名~");
    //搜索栏美化样式表
    searchLine->setStyleSheet("QLineEdit{font: bold  large \"Times New Roman\";font-size:18px;color:rgb(55,100,255);height:20px;border:4px solid rgb(155,200,33);border-radius:1px;selection-color:pink}"
                         "QLineEdit{ border: 0px groove rgb(255,0,0);color:rgb(201,201,201);  background-color: rgb(36,37, 39);}"
                         "QLineEdit:hover{ border: 2px groove rgb(26,58,93);color:rgb(201,201,201);  background-color: rgb(36,37, 39); }"
                         "QLineEdit:!hover{border: 2px groove rgb(36,37, 39);color:rgb(75,79, 81);  background-color: rgb(36,37, 39);}"
                         "QLineEdit:focus {border: 9px groove rgb(0,0,255);color:rgb(0,0,255);  background-color: rgb(36,37, 39););}"
                              );
    connect(searchLine,SIGNAL(returnPressed()),this,SLOT(searchVideo()));
    connect(searchBtn,SIGNAL(clicked()),this,SLOT(searchVideo()));
    playerListBtn=new QPushButton(this);
    onlineListBtn=new QPushButton(this);

    playerListBtn->setFixedSize(241,32);
    playerListBtn->setStyleSheet("QPushButton{text-align : left;}"
                                 "QPushButton{border-image: url(:/images/listBtn03);}"
                                 "QPushButton:hover{border-image: url(:/images/listBtn04);}"
                                 "QPushButton:pressed{border-image:url(:/images/listBtn06);}");

    onlineListBtn->setFixedSize(241,32);
    onlineListBtn->setStyleSheet("QPushButton{text-align:left;}"
                                 "QPushButton{border-image:url(:/images/listBtn01);}"
                                 "QPushButton:hover{border-image:url(:/images/listBtn02);}"
                                 "QPushButton:pressed{border-image:url(:/images/listBtn05)}");

    //设置字体大小，样式和颜色
    playerListBtn->setFont(QFont("幼圆",12,100));
    onlineListBtn->setFont(QFont("幼圆",12,100));
    QPalette   palforBtn1;
    palforBtn1.setColor(QPalette::ButtonText, QColor(192,198,199));
    playerListBtn->setPalette(palforBtn1);
    onlineListBtn->setPalette(palforBtn1);
    playerListBtn->setText("本地列表");
    onlineListBtn->setText("在线列表");
    //设置鼠标样式
    playerListBtn->setCursor(Qt::PointingHandCursor);
    onlineListBtn->setCursor(Qt::PointingHandCursor);
    connect(playerListBtn,SIGNAL(clicked()),this,SLOT(changeList()));
    connect(onlineListBtn,SIGNAL(clicked()),this,SLOT(changeList()));

    //设置本地列表
    myListWidget=new MyListWidget(this);
    //设置最大和最小规格
    myListWidget->setMaximumWidth(241);
    myListWidget->setMinimumWidth(225);
    myListWidget->setAcceptDrops(false);
    palette1.setColor(QPalette::Base,QColor(7,7,7));
    myListWidget->setAutoFillBackground(true);
    myListWidget->setPalette(palette1);
    myListWidget->setCursor(QCursor(Qt::ArrowCursor));
    myListWidget->setSpacing(0);
    myListWidget->setStyleSheet("QToolTip {border: 2px solid rgb(43,43,45);color:white;background-color: rgb(27,27,28);padding: 5px; border-radius: 3px;opacity: 200;}"
                                  "QListWidget{border: 2px groove rgb(43,43,43); font: 75 15pt ;color: rgb(70, 153, 252);background-color: rgb(7, 7, 7,255);}"
                                  "QListWidget::item{font: 75 20pt ;color: rgb(201, 201, 201);background-color: rgb(7, 7, 7,255);}"
                                  "QListWidget::item:selected{font: 75 20pt ;color: rgb(58, 142, 233);background-color: rgb(21, 29, 46,255);}"
                                  "QListWidget::item:hover:!selected {font: 75 20pt;color:rgb(201,201,201);background-color:rgb(27,27,27);}"
                                  "QListWidget::item:hover:selected {font: 75 20pt;color:rgb(58, 142, 233);background-color:rgb(21, 29, 46,255);}"
                                  "QListWidget::scrollbar {background-color:rgb(27,27,28);}" );

    //设置本地列表
    onlineListWidget=new QListWidget(this);
    //设置最大和最小规格
    onlineListWidget->setMaximumWidth(241);
    onlineListWidget->setMinimumWidth(225);
    onlineListWidget->setAcceptDrops(false);
    palette1.setColor(QPalette::Base,QColor(7,7,7));
    onlineListWidget->setAutoFillBackground(true);
    onlineListWidget->setPalette(palette1);
    onlineListWidget->setCursor(QCursor(Qt::ArrowCursor));
    onlineListWidget->setSpacing(0);
    onlineListWidget->setStyleSheet("QToolTip {border: 2px solid rgb(43,43,45);color:white;background-color: rgb(27,27,28);padding: 5px; border-radius: 3px;opacity: 200;}"
                                  "QListWidget{border: 2px groove rgb(43,43,43); font: 75 15pt ;color: rgb(70, 153, 252);background-color: rgb(7, 7, 7,255);}"
                                  "QListWidget::item{font: 75 20pt ;color: rgb(201, 201, 201);background-color: rgb(7, 7, 7,255);}"
                                  "QListWidget::item:selected{font: 75 20pt ;color: rgb(58, 142, 233);background-color: rgb(21, 29, 46,255);}"
                                  "QListWidget::item:hover:!selected {font: 75 20pt;color:rgb(201,201,201);background-color:rgb(27,27,27);}"
                                  "QListWidget::item:hover:selected {font: 75 20pt;color:rgb(58, 142, 233);background-color:rgb(21, 29, 46,255);}"
                                  "QListWidget::scrollbar {background-color:rgb(27,27,28);}" );
    //初始时在线列表隐藏
    onlineListWidget->hide();
    //列表的滑条样式美化样式表
    myListWidget->horizontalScrollBar()->setStyleSheet("QScrollBar:horizontal {"
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

    myListWidget->verticalScrollBar()->setStyleSheet("QScrollBar:vertical {"
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
    onlineListWidget->horizontalScrollBar()->setStyleSheet("QScrollBar:horizontal {"
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

    onlineListWidget->verticalScrollBar()->setStyleSheet("QScrollBar:vertical {"
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
    //列表栏布局
    listLayout=new QVBoxLayout(this);
    listLayout->addWidget(searchLine);
    listLayout->addWidget(playerListBtn);
    listLayout->addWidget(myListWidget);
    listLayout->addWidget(onlineListBtn);
    listLayout->addWidget(onlineListWidget);


}
//控制列表栏的隐藏和显示
void MainWindow::changeList(){
    if(myListWidget->isHidden()){
        myListWidget->show();
        onlineListWidget->hide();
        playerListBtn->setStyleSheet("QPushButton{text-align : left;}"       //字体左对齐
                                     "QPushButton{border-image: url(:/images/listBtn03);}"
                                     "QPushButton:hover{border-image: url(:/images/listBtn04);}"
                                     "QPushButton:pressed{border-image:url(:/images/listBtn06);}");
        onlineListBtn->setStyleSheet("QPushButton{text-align:left;}"
                                     "QPushButton{border-image:url(:/images/listBtn01);}"
                                     "QPushButton:hover{border-image:url(:/images/listBtn02);}"
                                     "QPushButton:pressed{border-image:url(:/images/listBtn05)}");
    }
    else{
        myListWidget->hide();
        onlineListWidget->show();
        playerListBtn->setStyleSheet("QPushButton{text-align:left;}"
                                     "QPushButton{border-image:url(:/images/listBtn01);}"
                                     "QPushButton:hover{border-image:url(:/images/listBtn02);}"
                                     "QPushButton:pressed{border-image:url(:/images/listBtn05)}");
        onlineListBtn->setStyleSheet("QPushButton{text-align:left;}"
                                     "QPushButton{border-image:url(:/images/listBtn03);}"
                                     "QPushButton:hover{border-image:url(:/images/listBtn04);}"
                                     "QPushButton:pressed{border-image:url(:/images/listBtn06)}");
    }
    this->setFocus();
}
/*重写右键事件*/
void MainWindow::contextMenuEvent(QContextMenuEvent *event){
    QSound::play(":/sounds/press.wav");
    //获得鼠标位置
    QCursor cur=this->cursor();

    QAction *openFileAction;
    QAction *exitAction;
    QAction *aboutAction;
    openFileAction=new QAction(" Open  打开",this);
    openFileAction->setShortcut(tr("Ctrl+O"));
    openFileAction->setStatusTip("打开一个文件");
    exitAction=new QAction(" Exit  退出",this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip("退出程序");
    aboutAction=new QAction(" About  关于",this);
    QMenu *rightMenu=new QMenu();
    rightMenu->setAutoFillBackground(true);
    rightMenu->addAction(openFileAction);
    rightMenu->addAction(exitAction);
    rightMenu->addSeparator();
    rightMenu->addAction(aboutAction);
    rightMenu->setStyleSheet("QMenu{"
                            "padding:5px;"
                                     "background:white;"
                            "border:1px solid gray;"
                             "}"
                            " QMenu::item{"
                            "padding:0px 40px 0px 30px;"
                            "height:25px;"
                             "}"
                             "QMenu::item:selected:enabled{"
                             "       background:rgb(90,182,253);"
                             "       color:white;"
                             "}"
                             " QMenu::item:selected:!enabled{"
                             "       background:transparent;"
                             "}"
                             "QMenu::separator{"
                                    "height:1px;"
                                    "background:lightgray;"
                            "margin:5px 0px 5px 0px;"
                             "}");
    connect(openFileAction,SIGNAL(triggered()),this,SLOT(openFile()));
    connect(exitAction,SIGNAL(triggered()),this,SLOT(close()));
    rightMenu->exec(event->globalPos());
}

/*析构函数*/
MainWindow::~MainWindow()
{

}
/*打开文件槽函数*/
void MainWindow::openFile()
{
    QSound::play(":/sounds/press.wav");
    /*打开文件选择框*/
    QString fileOpen = QFileDialog::getOpenFileName(this,tr("Load a file"), "~");
    qDebug()<<"openFile"+fileOpen;
    /*因为getOpenFileName得到的文件名是类//似于C:/Hello/test.avi,与windows下的路径名不匹配，所以需要这一步转换*/
    fileOpen.replace("/", "\\");
    emit startLocalVedio(fileOpen);
}
/* 点击视频选项卡触发的槽函数 */
void MainWindow::setVideoState(){
//    QPalette   p1;
//    p1.setColor(QPalette::ButtonText, QColor(183,219,251));
//    QPalette   p2;
//    p2.setColor(QPalette::ButtonText, QColor(39,125,248));
    QSound::play(":/sounds/press.wav");
    switch(tabState){
    case VIDEOSTATE:break;
    case SEARCHSTATE:
        tabState=VIDEOSTATE;

//        titleBar->showVideoWidget->setPalette(p1);

        titleBar->showVideoWidget->setStyleSheet("QPushButton{border-image:url(:/images/Tabbutton.png);}"
                                                 "QPushButton:hover{border-image:url(:/images/Tabbutton.png);}"
                                                 "QPushButton:pressed{border-image:url(:/images/Tabbutton.png);}");
//        titleBar->showSearch->setPalette(p2);
        titleBar->showSearch->setStyleSheet("QPushButton{background-color:rgba(0,0,0,0);}");
        emit changeState(0);
        break;
    case BROWSERSTATE:
        tabState=VIDEOSTATE;
//        titleBar->showVideoWidget->setPalette(p1);
        titleBar->showVideoWidget->setStyleSheet("QPushButton{border-image:url(:/images/Tabbutton.png);}"
                                                 "QPushButton:hover{border-image:url(:/images/Tabbutton.png);}"
                                                 "QPushButton:pressed{border-image:url(:/images/Tabbutton.png);}");
//        titleBar->showBrowser->setPalette(p2);
        titleBar->showBrowser->setStyleSheet("QPushButton{background-color:rgba(0,0,0,0);}");
        emit changeState(0);
        break;
    }
}
/* 点击搜索选项卡触发的槽函数 */
void MainWindow::setSearchState(){
//    QPalette   p1;
//    p1.setColor(QPalette::ButtonText, QColor(183,219,251));
//    QPalette   p2;
//    p2.setColor(QPalette::ButtonText, QColor(39,125,248));
    QSound::play(":/sounds/press.wav");
    switch(tabState){
    case SEARCHSTATE:break;
    case BROWSERSTATE:
        tabState=SEARCHSTATE;
//        titleBar->showSearch->setPalette(p1);
        titleBar->showSearch->setStyleSheet("QPushButton{border-image:url(:/images/Tabbutton.png);}"
                                                 "QPushButton:hover{border-image:url(:/images/Tabbutton.png);}"
                                                 "QPushButton:pressed{border-image:url(:/images/Tabbutton.png);}");
//        titleBar->showBrowser->setPalette(p2);
        titleBar->showBrowser->setStyleSheet("QPushButton{background-color:rgba(0,0,0,0);}");
        emit changeState(1);
        break;
    case VIDEOSTATE:
        tabState=SEARCHSTATE;
//        titleBar->showSearch->setPalette(p1);
        titleBar->showSearch->setStyleSheet("QPushButton{border-image:url(:/images/Tabbutton.png);}"
                                                 "QPushButton:hover{border-image:url(:/images/Tabbutton.png);}"
                                                 "QPushButton:pressed{border-image:url(:/images/Tabbutton.png);}");
//        titleBar->showVideoWidget->setPalette(p2);
        titleBar->showVideoWidget->setStyleSheet("QPushButton{background-color:rgba(0,0,0,0);}");
        emit changeState(1);
        break;
    }
}
/* 点击浏览器选项卡触发的槽函数 */
void MainWindow::setBrowserState(){
//    QPalette   p1;
//    p1.setColor(QPalette::ButtonText, QColor(183,219,251));
//    QPalette   p2;
//    p2.setColor(QPalette::ButtonText, QColor(39,125,248));
    QSound::play(":/sounds/press.wav");
    switch(tabState){
    case BROWSERSTATE:break;
    case SEARCHSTATE:
        tabState=BROWSERSTATE;
//        titleBar->showBrowser->setPalette(p1);
        titleBar->showBrowser->setStyleSheet("QPushButton{border-image:url(:/images/Tabbutton.png);}"
                                                 "QPushButton:hover{border-image:url(:/images/Tabbutton.png);}"
                                                 "QPushButton:pressed{border-image:url(:/images/Tabbutton.png);}");
//        titleBar->showSearch->setPalette(p2);
        titleBar->showSearch->setStyleSheet("QPushButton{background-color:rgba(0,0,0,0);}");
        emit changeState(2);
        break;
    case VIDEOSTATE:
        tabState=BROWSERSTATE;
//        titleBar->showBrowser->setPalette(p1);
        titleBar->showBrowser->setStyleSheet("QPushButton{border-image:url(:/images/Tabbutton.png);}"
                                                 "QPushButton:hover{border-image:url(:/images/Tabbutton.png);}"
                                                 "QPushButton:pressed{border-image:url(:/images/Tabbutton.png);}");
//        titleBar->showVideoWidget->setPalette(p2);
        titleBar->showVideoWidget->setStyleSheet("QPushButton{background-color:rgba(0,0,0,0);}");
        emit changeState(2);
        break;
    }
}
/* 显示或者隐藏播放列表 */
void MainWindow::showOrHideList(){
    QSound::play(":/sounds/press.wav");
    if(isListHide==false){
        searchLine->hide();
        playerListBtn->hide();
        myListWidget->hide();
        onlineListBtn->hide();
        onlineListWidget->hide();
        controlWidget->showListBtn->setStyleSheet("QPushButton{border-image:url(:/images/showListBtn01);}"
                                                  "QPushButton:hover{border-image:url(:/images/showListBtn02);}"
                                                  "QPushButton:pressed{border-image:url(:/images/showListBtn03);}");

        isListHide=true;
    }
    else{
        searchLine->show();
        playerListBtn->show();
        myListWidget->show();
        onlineListBtn->show();
        onlineListWidget->hide();
        controlWidget->showListBtn->setStyleSheet("QPushButton{border-image:url(:/images/showListBtn04);}"
                                                  "QPushButton:hover{border-image:url(:/images/showListBtn05);}"
                                                  "QPushButton:pressed{border-image:url(:/images/showListBtn06);}");
        isListHide=false;
    }
}
/* 设置全屏 */
void MainWindow::setFullScreen(){
    QSound::play(":/sounds/press.wav");
    if(!isFullScreen()){
        titleBar->hide();
        searchLine->hide();
        playerListBtn->hide();
        myListWidget->hide();
        onlineListBtn->hide();
        onlineListWidget->hide();
        isListHide=true;
        controlWidget->showListBtn->setStyleSheet("QPushButton{border-image:url(:/images/showListBtn01);}"
                                                  "QPushButton:hover{border-image:url(:/images/showListBtn02);}"
                                                  "QPushButton:pressed{border-image:url(:/images/showListBtn03);}");
        controlWidget->fullScreenBtn->setStyleSheet("QPushButton{border-image:url(:/images/fullScreenBtn06);}"
                                                    "QPushButton:hover{border-image:url(:/images/fullScreenBtn05);}"
                                                    "QPushButton:pressed{border-image:url(:/images/fullScreenBtn07);}");
        showFullScreen();
    }else{
        titleBar->show();
        searchLine->show();
        playerListBtn->show();
        myListWidget->show();
        onlineListBtn->show();
        onlineListWidget->hide();
        isListHide=false;
        controlWidget->showListBtn->setStyleSheet("QPushButton{border-image:url(:/images/showListBtn04);}"
                                                  "QPushButton:hover{border-image:url(:/images/showListBtn05);}"
                                                  "QPushButton:pressed{border-image:url(:/images/showListBtn06);}");
        controlWidget->fullScreenBtn->setStyleSheet("QPushButton{border-image:url(:/images/fullScreenBtn01);}"
                                                    "QPushButton:hover{border-image:url(:/images/fullScreenBtn02);}"
                                                    "QPushButton:pressed{border-image:url(:/images/fullScreenBtn03);}");
        showNormal();
    }
}
/* 重写拖放中的拖事件 */
void MainWindow::dragEnterEvent(QDragEnterEvent *event){
    if (event->mimeData()) {                                                      //检测事件的mimeData
            event->acceptProposedAction();
        }
}
/* 重写拖放中的放事件 */
void MainWindow::dropEvent(QDropEvent *event){
    QList<QUrl> urls=event->mimeData()->urls();
    if(urls.isEmpty()){
        return;
    }
    qDebug()<<"drop event!";
    QString fileName=urls.first().toLocalFile();
    fileName.replace("/", "\\");
    vedioWidget->stop();
    emit startLocalVedio(fileName);
}
/* 上一个视频 */
void MainWindow::preVideo(){
    QSound::play(":/sounds/press.wav");
    if(myListWidget->currentItem()==NULL)
        {
            vedioWidget->stop();
            return ;
        }

        if(!myListWidget)
        {
            vedioWidget->stop();
            return;
        }
        if(myListWidget->count()==0)
        {
            vedioWidget->stop();
            return;
        }

        if(myListWidget->currentRow()==0)
        {
            //链接表头与表尾
            myListWidget->setCurrentItem(myListWidget->item((myListWidget->count()-1)));
        }
        else
        {
            myListWidget->setCurrentItem(myListWidget->item(myListWidget->currentRow()-1));
        }
        vedioWidget->stop();
        QString fileDir=myListWidget->currentItem()->data(Qt::UserRole).toString();
        emit startLocalVedio(fileDir);
}
/* 下一个视频 */
void MainWindow::nextVideo(){
    QSound::play(":/sounds/press.wav");
    if(myListWidget->currentItem()==NULL)
        {
            vedioWidget->stop();
            return ;
        }

        if(!myListWidget)
        {
            vedioWidget->stop();
            return;
        }
        if(myListWidget->count()==0)
        {
            vedioWidget->stop();
            return;
        }

        if(myListWidget->currentRow()==(myListWidget->count()-1))
        {
            //链接表头与表尾
            myListWidget->setCurrentItem(myListWidget->item(0));
        }
        else
        {
            //下一个
            myListWidget->setCurrentItem(myListWidget->item(myListWidget->currentRow()+1));
        }
        qDebug()<<"nextVideo,begin stop current video";
        vedioWidget->stop();
        qDebug()<<"nextVideo,stop current video";
        QString fileDir=myListWidget->currentItem()->data(Qt::UserRole).toString();
        emit startLocalVedio(fileDir);
}
/* 窗口改变时触发的事件，删去后最小化复原时会出现某些控件不见的bug */
void MainWindow::changeEvent(QEvent *e){
    if( (e->type() == QEvent::WindowStateChange))
        {
            if((this->windowState() & Qt::WindowMinimized))
            {

            }else{


            }
        }
}
void MainWindow::playSound(){
    QSound::play(":/sounds/boot.wav");
}
void MainWindow::searchVideo(){
    QString url="http://so.iqiyi.com/so/q_"+searchLine->text();
    emit searchWebVedio(url);
}
