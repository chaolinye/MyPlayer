#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>
#include <QMouseEvent>
#include <QPoint>
#include <QPushButton>
#include <QToolButton>
#include <QHBoxLayout>
#include <QLabel>

enum eBtnMoustState{
     eBtnStateNone,//无效
     eBtnStateDefault,//默认值(如按钮初始显示)
     eBtnStateHover,//鼠标移到按钮上状态
     eBtnStatePress//鼠标按下按钮时状态
 };
class TitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit TitleBar(QWidget *parent = 0);
    QAction *openFileAction;
    QAction *exitAction;
    QAction *aboutAction;
    QPushButton *showVideoWidget;
    QPushButton *showSearch;
    QPushButton *showBrowser;
    QPushButton *maxBtn;

signals:
    //缩小、放大、恢复、关闭等信号
    void signal_min();
    void signal_max();
    void signal_restore();
    void signal_close();
protected:
    /* 重写鼠标事件，使能够对自定义标题栏进行拖拉等操作 */
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *);
//    bool eventFilter(QObject *, QEvent *);

public slots:
    void maxRestore();
private:
    QPoint ptPress;
    QPoint ptMove;
    bool isLeftButtonPress;

    QPushButton *minBtn;
    QPushButton *exitBtn;
    QPushButton *logo;
    QMenu *mainMenu;

    QHBoxLayout *layout;

    void init();

    void setWidgetStyle();

//    void createEventFiter();

//    void setBtnIcon(QToolButton *pBtn,eBtnMoustState state,bool bInit=false);

//    const QString getBtnImagePath(QToolButton *pBtn,bool bInit/*=false*/);


};

#endif // TITLEBAR_H
