#ifndef BROWSERWIDGET_H
#define BROWSERWIDGET_H

#include <QWidget>
#include "addressbar.h"
#include <QWebView>
#include <QGridLayout>
#include <QUrl>
#include <QTabWidget>
#include <QLabel>

/*
 * 浏览器类,用于网络视频的播放
*/
class BrowserWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BrowserWidget(QWidget *parent = 0);

    /*析构函数*/
    ~BrowserWidget();

signals:

protected:
    /*重载关闭窗口的事件,窗口关闭时销毁窗口*/
    void closeEvent(QCloseEvent *event);

public slots:
    void loadPage();
    void homePage();
    void forwardPage();
    void backPage();
    void refreshLine();
    void refreshPage();
    void handleNewTab(QUrl);
    void loadPart(int);
    void loadFinish(bool);
    void handleTabClosed(int);
    void loadWebPage(QString);

private:
    QString HOMEPAGE;
    /*地址栏*/
    AddressBar *addressBar;
    /*浏览器播放部件*/
    QWebView *browserView;
    /*网格布局*/
    QGridLayout *layout;
    /*选项卡*/
    QTabWidget * tabWidget;

    QWidget *statusWidget;
    QLabel *statusLabel;
    QList<QWebView *> viewlist;


    void refreshState(QString);

    bool hasLoad;

};

#endif // BROWSERWIDGET_H
