#include "mylistwidget.h"
#include <QDebug>
#include <QTextStream>
#include <QFile>
#include <QFileInfo>
#include <QDebug>
#include <QCoreApplication>
#include <QMenu>
#include <QTextCodec>

MyListWidget::MyListWidget(QWidget *parent) :
    QListWidget(parent)
{
    setFixedWidth(180);
    connect(this,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(click2(QListWidgetItem*)));
    setStyleSheet("background-image:url(:images/Background.jpg)");
    init();

}
void MyListWidget::addFile(QString fileDir)
{
    QString fileName=QFileInfo(fileDir).fileName();
    if(fileName=="")
        return;
    for(int i=0;i<count();i++)
    {
        if(fileName==this->item(i)->text())
            return;
    }
    //添加列表项
    QListWidgetItem * list1 = new QListWidgetItem(fileName, this);
    list1->setData(Qt::UserRole,fileDir);
    list1->setToolTip(fileName);
    this->insertItem(Qt::UserRole, list1);
    this->setCurrentItem(this->item(this->count()-1));
    QString runPath = QCoreApplication::applicationDirPath();
    qDebug()<<"列表初始化";
    QFile file(runPath+"/FileList.txt");
    if(file.open(QIODevice::WriteOnly|QFile::Append|QFile::Text))
    {
        QTextStream out(&file);
        QTextCodec *codec=QTextCodec::codecForName("UTF-8");
        out.setCodec(codec);
        out<<fileDir+"\n";
        file.close();
    }

}
void MyListWidget::click2(QListWidgetItem* item)
{
    QString fileName=item->data(Qt::UserRole).toString();
    qDebug()<<fileName+" is clicked.";
    emit sendFileName(fileName);
}
void MyListWidget::init()
{
    //获取项目路径
    QString runPath = QCoreApplication::applicationDirPath();
    qDebug()<<"列表初始化";
    QFile file(runPath+"/FileList.txt");
    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream out(&file);
        QTextCodec *codec=QTextCodec::codecForName("UTF-8");
        out.setCodec(codec);
        while(!out.atEnd())
        {
            QString fileDir=out.readLine();
            QString fileName=QFileInfo(fileDir).fileName();
            if(fileName!=""){
                QListWidgetItem * list1 = new QListWidgetItem(fileName, this);
                list1->setData(Qt::UserRole,fileDir);
                list1->setToolTip(fileName);
                this->insertItem(Qt::UserRole, list1);
            }
        }
        file.close();

    }
}
void MyListWidget::contextMenuEvent(QContextMenuEvent *)
{
    QMenu *popMenu = new QMenu(this);
    QAction *action1 = new QAction(tr("删除选中项") , this);
    QAction *action2 = new QAction(tr("删除全部") , this);

    connect(action1 , SIGNAL(triggered(bool)) , this , SLOT(deleteOne()));
    connect(action2 , SIGNAL(triggered(bool)) , this , SLOT(deleteAll()));

    if((currentitem=this->itemAt(mapFromGlobal(QCursor::pos()))) != NULL)
    {
        popMenu->addAction(action1);
        popMenu->addAction(action2);
        popMenu->setStyleSheet("QMenu{"
                               "padding:5px;"
                                        "background:rgb(46,46,46);"
                               "color:white;"
                               "border:1px solid gray;"
                                "}"
                               " QMenu::item{"
                               "padding:0px 40px 0px 30px;"
                               "height:25px;"
                                "}"
                                "QMenu::item:selected:enabled{"
                                "       background:rgb(25,25,25);"
                                "       color:white;"
                                "}"
                                " QMenu::item:selected:!enabled{"
                                "       background:transparent;"
                                "}"
                                "QMenu::separator{"
                                       "height:1px;"
                                       "background:rgb(25,25,25);"
                               "margin:5px 0px 5px 0px;"
                                "}");
        popMenu->exec(QCursor::pos()); //菜单出现的位置为当前鼠标的位置

    }


    delete popMenu;
    delete action1;
    delete action2;
}

void MyListWidget::deleteOne()
{
    qDebug()<<"修改前总数"<<count();
    if(currentitem==NULL)
        return;
    int r=this->row(currentitem);
    delete takeItem(r);
    QString runPath = QCoreApplication::applicationDirPath();
    qDebug()<<"修改本地记录";
    QFile file(runPath+"/FileList.txt");
    if(file.open(QIODevice::WriteOnly|QFile::Text))
    {
        for(int i=0;i<count();i++)
        {
            qDebug()<<count();
            QTextStream out(&file);
            QTextCodec *codec=QTextCodec::codecForName("UTF-8");
            out.setCodec(codec);
            out<<this->item(i)->data(Qt::UserRole).toString()+"\n";

        }
        file.close();
    }


}
void MyListWidget::deleteAll()
{
    clear();
    QString runPath = QCoreApplication::applicationDirPath();
    qDebug()<<"修改本地记录";
    QFile file(runPath+"/FileList.txt");
    if(file.open(QIODevice::WriteOnly|QFile::Text))
    {
        QTextStream out(&file);
        QTextCodec *codec=QTextCodec::codecForName("UTF-8");
        out.setCodec(codec);
        out<<"";
        file.close();
    }

}


