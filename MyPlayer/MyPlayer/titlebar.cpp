#include "titlebar.h"
#include "mainwindow.h"
#include <QRect>



TitleBar::TitleBar(QWidget *parent) :
    QWidget(parent)
{
    isLeftButtonPress=false;
    init();
    setWidgetStyle();

}
void TitleBar::init()
{
    this->setAutoFillBackground(true);

    QPixmap pi;
    pi.load(":/images/titlebar.png");
    QPalette p=this->palette();
    p.setBrush(QPalette::Window,QBrush(pi));

    this->setPalette(p);
    /* 设置图片透明度 */
    setWindowOpacity(1.0);
    /*初始化标题栏图标*/
    logo=new QPushButton(this);
    logo->setFixedSize(26,26);
    logo->setIconSize(QSize(26,26));
    logo->setStyleSheet("QPushButton{border-image:url(:/images/logo1.png);}"
                        "QPushButton:hover{border-image:url(:/images/logo1.png);}"
                        "QPushButton:press{border-image:url(:/images/logo1.png);}"
                        "QPushButton::menu-indicator{image:None;}");
    openFileAction=new QAction(" Open  打开",this);
    openFileAction->setShortcut(tr("Ctrl+O"));
    openFileAction->setStatusTip("打开一个文件");
    exitAction=new QAction(" Exit  退出",this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip("退出程序");
    aboutAction=new QAction(" About  关于",this);
    mainMenu=new QMenu();
    mainMenu->setAutoFillBackground(true);
    mainMenu->addAction(openFileAction);
    mainMenu->addAction(exitAction);
    mainMenu->addSeparator();
    mainMenu->addAction(aboutAction);
    mainMenu->setStyleSheet("QMenu{"
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
    logo->setMenu(mainMenu);

    /* 初始化标题栏选项卡 */
    showVideoWidget=new QPushButton(this);
    showVideoWidget->setFixedSize(87,34);
    showVideoWidget->setStyleSheet("QPushButton{border-image:url(:/images/Tabbutton.png);}"
                                   "QPushButton:hover{border-image:url(:/images/Tabbutton.png);}"
                                   "QPushButton:pressed{border-image:url(:/images/Tabbutton.png);}");
    showVideoWidget->setFont(QFont("幼圆",12,100));
    QPalette   palforBtn;
    palforBtn.setColor(QPalette::ButtonText, QColor(183,219,251));
    showVideoWidget->setPalette(palforBtn);
    showVideoWidget->setText("播放");

    showSearch=new QPushButton(this);
    showSearch->setFixedSize(87,34);
    showSearch->setStyleSheet("QPushButton{background-color:rgba(0,0,0,0);}");
    showSearch->setFont(QFont("幼圆",12,100));
    QPalette   palforSear;
    palforSear.setColor(QPalette::ButtonText, QColor(39,125,248));
    showSearch->setPalette(palforSear);
    showSearch->setText("搜索");

    showBrowser=new QPushButton(this);
    showBrowser->setFixedSize(87,34);
    showBrowser->setFont(QFont("幼圆",12,100));
    showBrowser->setStyleSheet("QPushButton{background-color:rgba(0,0,0,0);}");
    QPalette palfornet;
    palfornet.setColor(QPalette::ButtonText,QColor(39,125,248));
    showBrowser->setPalette(palfornet);
    showBrowser->setText("浏览器");

    maxBtn=new QPushButton(this);
    maxBtn->setCursor(Qt::PointingHandCursor);
    maxBtn->setFixedSize(29,32);
    maxBtn->setIconSize(QSize(29, 32));
    maxBtn->setStyleSheet("QPushButton{border-image: url(:/images/max01.png);}"
                                "QPushButton:hover{border-image: url(:/images/max02.png);}"
                                "QPushButton:pressed{border-image: url(:/images/max03.png);}");
    connect(maxBtn,SIGNAL(clicked()),this,SLOT(maxRestore()));


    minBtn=new QPushButton(this);
    minBtn->setCursor(Qt::PointingHandCursor);
    minBtn->setFixedSize(29,32);
    minBtn->setIconSize(QSize(29, 32));
    minBtn->setStyleSheet("QPushButton{border-image: url(:/images/min01.png);}"
                                "QPushButton:hover{border-image: url(:/images/min02.png);}"
                                "QPushButton:pressed{border-image: url(:/images/min03.png);}");
    connect(minBtn,SIGNAL(clicked()),this,SIGNAL(signal_min()));

    exitBtn=new QPushButton(this);
    exitBtn->setCursor(Qt::PointingHandCursor);
    exitBtn->setFixedSize(38,32);
    exitBtn->setIconSize(QSize(38, 32));
    exitBtn->setStyleSheet("QPushButton{border-image: url(:/images/close01.png);}"
                                "QPushButton:hover{border-image: url(:/images/close02.png);}"
                                "QPushButton:pressed{border-image: url(:/images/close03.png);}");
    connect(exitBtn,SIGNAL(clicked()),this,SIGNAL(signal_close()));

    //水平布局
    layout = new QHBoxLayout(this);
    //添加部件
    layout->addSpacing(10);
    layout->addWidget(logo);
    layout->addSpacing(30);
    layout->addWidget(showVideoWidget);
    layout->addWidget(showSearch);
    layout->addWidget(showBrowser);

    //添加伸缩项
    layout->addStretch(1);
    //添加部件
    layout->addWidget(minBtn);
    layout->addWidget(maxBtn);
    layout->addWidget(exitBtn);
    layout->addSpacing(0);
    //设置Margin
    layout->setContentsMargins(0,0,0,0);
    //设置部件之间的space
    layout->setSpacing(0);
    setLayout(layout);



}

void TitleBar::maxRestore()
{
    if(MainWindow::isMax==true)
    {
        maxBtn->setStyleSheet("QPushButton{border-image: url(:/images/max01.png);}"
                                    "QPushButton:hover{border-image: url(:/images/max02.png);}"
                                    "QPushButton:pressed{border-image: url(:/images/max03.png);}");
        emit signal_restore();
        MainWindow::isMax=false;
    }
    else{
        maxBtn->setStyleSheet("QPushButton{border-image: url(:/images/nor01.png);}"
                                    "QPushButton:hover{border-image: url(:/images/nor02.png);}"
                                    "QPushButton:pressed{border-image: url(:/images/nor03.png);}");
        emit signal_max();
        MainWindow::isMax=true;
    }
}


//设置子部件样式(qss)
void TitleBar::setWidgetStyle()
{
    //设置标签的文本颜色，大小等以及按钮的边框
    setStyleSheet("QLabel{color:#CCCCCC;font-size:12px;font-weight:bold;}QToolButton{border:0px;}");

}

//鼠标按下事件
void TitleBar::mousePressEvent(QMouseEvent *event)
{
    qDebug()<<"鼠标按下标题栏";
    if (event->button() == Qt::LeftButton)
    {
        qDebug()<<"左键";
     QRect rect = this->rect();
     if(!rect.contains(event->pos()))
        {
            qDebug()<<"222";
            event->ignore();
            return;
        }
        ptPress = event->globalPos();
             qDebug()<<ptPress;
        isLeftButtonPress = true;
    }
    event->ignore();
}
//鼠标移动事件
void TitleBar::mouseMoveEvent(QMouseEvent *event)
{
    if(isLeftButtonPress)
    {
        qDebug()<<"移动标题栏";
        ptMove = event->globalPos();
        qDebug()<<ptMove;
        //移动主窗口
        MainWindow *pMainWindow = ((MainWindow*)(parent()->parent()));
        qDebug()<<"hahah";
        pMainWindow->move(pMainWindow->pos()+ptMove-ptPress);
        qDebug()<<"移动";
        //重新设置m_ptPress;
        ptPress = ptMove;
    }
    event->ignore();
}
//鼠标释放事件
void TitleBar::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        isLeftButtonPress = false;
    }
     event->ignore();
}

