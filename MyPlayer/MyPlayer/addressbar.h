#ifndef ADDRESSBAR_H
#define ADDRESSBAR_H

#include <QWidget>
#include <QUrl>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>

/*
 * 浏览器的地址栏部件
*/
class AddressBar : public QWidget
{
    Q_OBJECT
public:
    explicit AddressBar(QWidget *parent = 0);
    /*地址编辑条*/
    QLineEdit *addressEdit;
    //打开主页按钮动作
    QPushButton *homeBtn;
    //返回上一页按钮动作
    QPushButton *backBtn;
    //返回下一页按钮动作
    QPushButton *forwardBtn;
    //刷新按钮动作
    QPushButton *refreshBtn;
signals:

public slots:

private:


};

#endif // ADDRESSBAR_H
