#include "browserwidget.h"

BrowserWidget::BrowserWidget(QWidget *parent) :
    QWidget(parent)
{
    addressBar=new AddressBar(this);

    browserView=new QWebView(this);
    HOMEPAGE="http://www.baidu.com";
    tabWidget = new QTabWidget(this);
    tabWidget->setTabsClosable(true);
    tabWidget->setTabShape(QTabWidget::Triangular);

    /*设置相关浏览器的支持属性和插件*/
    browserView->settings()->setAttribute(QWebSettings::JavascriptEnabled,true);
    browserView->settings()->setAttribute(QWebSettings::PluginsEnabled,true);
    browserView->settings()->setAttribute(QWebSettings::JavascriptCanOpenWindows,true);
    browserView->settings()->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls,true);

    statusWidget=new QWidget(this);
    statusLabel=new QLabel(statusWidget);
    statusLabel->setMinimumHeight(15);
    statusLabel->setMinimumWidth(500);
    statusWidget->setMinimumHeight(15);

    QVBoxLayout * layout2=new QVBoxLayout(this);
    layout2->addWidget(addressBar);
    layout2->addWidget(tabWidget);
    layout2->addWidget(statusWidget);
    browserView->setFont(QFont("幼圆"));
    browserView->load(QUrl(HOMEPAGE));
    browserView->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
    int Index=tabWidget->addTab(browserView,"欢迎使用");
    tabWidget->setCurrentIndex(Index);
    tabWidget->setStyleSheet("border-color:white;color:black;");
    viewlist.append(browserView);
    addressBar->addressEdit->setText(HOMEPAGE);
    this->setLayout(layout2);
    connect(addressBar->addressEdit,SIGNAL(returnPressed()),this,SLOT(loadPage()));
    connect(addressBar->homeBtn,SIGNAL(clicked()),this,SLOT(homePage()));
    connect(addressBar->backBtn,SIGNAL(clicked()),this,SLOT(backPage()));
    connect(addressBar->forwardBtn,SIGNAL(clicked()),this,SLOT(forwardPage()));
    connect(addressBar->refreshBtn,SIGNAL(clicked()),this,SLOT(refreshPage()));

    connect(browserView, SIGNAL(linkClicked(QUrl)), this,SLOT(handleNewTab(QUrl)));
    connect(browserView, SIGNAL(loadProgress(int)), this, SLOT(refreshLine()));
    connect(browserView,SIGNAL(titleChanged(QString)),tabWidget,SLOT(setWindowTitle(QString)));

    connect(browserView, SIGNAL(loadProgress(int)), this,SLOT(loadPart(int)));
    connect(browserView, SIGNAL(loadFinished(bool)), this,SLOT(loadFinish(bool)));
    connect(tabWidget,SIGNAL(tabCloseRequested(int)),this,SLOT(handleTabClosed(int)));

}
/*打开网页*/
void BrowserWidget::loadPage(){
    QString str = addressBar->addressEdit->text();		//读取用户输入的网址

    //由于用户习惯输入缺省“http://”，因此需要判断是否自动添加
    if (str.size() > 3 && str[0] == 'w' && str[1] == 'w' && str[2] == 'w')
    {
        str = "http://" + str;
    }
    refreshState("accessing to " + str);	//更新状态栏
    QWebView * view=(QWebView*)tabWidget->currentWidget();
    view->load(QUrl(str));				//加载页面

    refreshLine();							//更新网址输入栏
}
void BrowserWidget::loadWebPage(QString str){
    //由于用户习惯输入缺省“http://”，因此需要判断是否自动添加
    if (str.size() > 3 && str[0] == 'w' && str[1] == 'w' && str[2] == 'w')
    {
        str = "http://" + str;
    }
    refreshState("accessing to " + str);	//更新状态栏
    QWebView * view=(QWebView*)tabWidget->currentWidget();
    view->load(QUrl(str));				//加载页面

    refreshLine();							//更新网址输入栏
}

//更新网址输入栏
void BrowserWidget::refreshLine()
{
    QWebView * view=(QWebView*)tabWidget->currentWidget();
    addressBar->addressEdit->setText(view->url().toString());
}
//更新状态栏信息
void BrowserWidget::refreshState(QString state)
{
    statusLabel->setText(state);
}
void BrowserWidget::homePage(){
    QWebView * view=(QWebView*)tabWidget->currentWidget();
    view->load(QUrl(HOMEPAGE));
    refreshLine();
}
void BrowserWidget::backPage(){
    QWebView * view=(QWebView*)tabWidget->currentWidget();
    view->back();
}
void BrowserWidget::forwardPage(){
    QWebView * view=(QWebView*)tabWidget->currentWidget();
    view->forward();
}
void BrowserWidget::refreshPage(){
    QWebView * view=(QWebView*)tabWidget->currentWidget();
    view->reload();
}
//void BrowserWidget::setSearchString(QString & urlstring)
//{
//    searchString=urlstring;
//    if(searchString!=NULL)
//    {
//        if(tabWidget->currentWidget()==NULL)
//            browserView->load("http://cn.bing.com/search?q="+searchString+"&go=&qs=n&form=QBLH&pq="+searchString+"&sc=8-4&sp=-1&sk=&cvid=508dc137d14d4a2c9c81d26dd563f31f");
//        else
//        {
//            QWebView * view=(QWebView *)netTab->currentWidget();
//            view->load("http://cn.bing.com/search?q="+searchString+"&go=&qs=n&form=QBLH&pq="+searchString+"&sc=8-4&sp=-1&sk=&cvid=508dc137d14d4a2c9c81d26dd563f31f");
//        }
//    }
//}

void BrowserWidget::handleNewTab(QUrl url)
{
    QWebView * newpageview=new QWebView(this);
    newpageview->setFont(QFont("幼圆"));
    newpageview->load(QUrl(url));
    newpageview->page()->setForwardUnsupportedContent(true);
    newpageview->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
    newpageview->settings()->setAttribute(QWebSettings::JavascriptEnabled,true);
    newpageview->settings()->setAttribute(QWebSettings::PluginsEnabled,true);
    newpageview->settings()->setAttribute(QWebSettings::JavascriptCanOpenWindows,true);
    newpageview->settings()->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls,true);

    connect(newpageview, SIGNAL(linkClicked(QUrl)), SLOT(handleNewTab(QUrl)));
    connect(newpageview, SIGNAL(loadProgress(int)), this, SLOT(refreshLine()));

    connect(newpageview, SIGNAL(loadProgress(int)), SLOT(loadPart(int)));
    connect(newpageview, SIGNAL(loadFinished(bool)), SLOT(loadFinish(bool)));

    int Index= tabWidget->addTab(newpageview,QWebSettings::iconForUrl(QUrl(url)),"新页面~");
    tabWidget->setCurrentIndex(Index);
    if(tabWidget->count()<5)
        tabWidget->setStyleSheet("border-color:white;color:black;");
    else if (tabWidget->count()<10)
    {
        int Tabwidth=tabWidget->width()/tabWidget->count();
        tabWidget->setStyleSheet(QString("QTabBar::tab{width:%1};").arg(Tabwidth)
                          +"border-color:white;color:black;");
    }
    viewlist.append(newpageview);
}

void BrowserWidget::handleTabClosed(int index)
{
    if(viewlist.length()==1)
        return ;
    if (index > viewlist.length() - 1)
        return;

    if(index+1>tabWidget->count()-1)
        tabWidget->setCurrentIndex(index-1);
    if(index-1<1)
        tabWidget->setCurrentIndex(index+1);

    tabWidget->removeTab(index);
    if(tabWidget->count()>=10)
        ;
    else if(tabWidget->count()>=5)
    {
        int Tabwidth=tabWidget->width()/tabWidget->count();
        tabWidget->setStyleSheet(QString("QTabBar::tab{width:%1};").arg(Tabwidth)
                          +"border-color:white;color:black;");
    }


    QWebView* view = viewlist[index];
    viewlist.removeAt(index);

    delete view;
}
//显示加载进度
void BrowserWidget::loadPart(int percent)
{
    if(percent > 50 && !hasLoad)
    {
        hasLoad = true;
    }

    QWebView * view=(QWebView*)tabWidget->currentWidget();

    tabWidget->setTabText(tabWidget->currentIndex(),view->title());	//更新窗口标题
    refreshState("accessing to " + view->url().toString() + "..." + QString::number(percent) + "%");
}

//处理页面加载完后的操作
void BrowserWidget::loadFinish(bool success)
{
    QWebView * view=(QWebView*)tabWidget->currentWidget();
    if (success)
    {
        tabWidget->setTabText(tabWidget->currentIndex(),view->title());
        refreshState(tr("Ready"));

    }
    else if (hasLoad)
    {
        refreshState(tr("Parts fail to load"));
    }
    else
    {
        view->load(QUrl("Resources//errorIndex.html"));	//加载失败提示
        refreshLine();
        refreshState(tr("Could not access network location"));
    }
    hasLoad = false;

    if (success || hasLoad)
    {
        if (view->title() != "errorPage")
        {
        }
    }
}
/*析构函数*/
BrowserWidget::~BrowserWidget()
{
    delete browserView;
    delete addressBar;

}

/*重载关闭窗口的事件,窗口关闭时销毁窗口*/
void BrowserWidget::closeEvent(QCloseEvent *)
{
    setAttribute(Qt::WA_DeleteOnClose);
}
