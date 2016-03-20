#ifndef SEARCHWIDGET_H
#define SEARCHWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QTableWidget>
#include <QLineEdit>

class SearchWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SearchWidget(QWidget *parent = 0);


signals:
    void openWebVideo(QString);

public slots:
     void startSearch();
     void doubleClick(int,int);
private:
    QPushButton *searchBtn;
    QLineEdit *searchLine;
    QTableWidget *tableWidget;

};

#endif // SEARCHWIDGET_H
