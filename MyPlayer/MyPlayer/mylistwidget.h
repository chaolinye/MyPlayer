#ifndef MYLISTWIDGET_H
#define MYLISTWIDGET_H

#include <QListWidget>
#include <QWidget>
#include <QListWidgetItem>
#include <QListWidgetItem>

/*播放本地文件记录列表类
 *
*/

class MyListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit MyListWidget(QWidget *parent = 0);

signals:
    void sendFileName(QString);
protected:
    void contextMenuEvent(QContextMenuEvent *);

public slots:
    /*增加文件列表项*/
    void addFile(QString fileName);
    /*列表项双击打开相应的文件*/
    void click2(QListWidgetItem* item);

    void deleteOne();

    void deleteAll();


private:
    /*初始化列表，从文件获取文件播放记录*/
    void init();

    QListWidgetItem *currentitem;
};

#endif // MYLISTWIDGET_H
