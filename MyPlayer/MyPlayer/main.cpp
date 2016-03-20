#include "mainwindow.h"
#include <QApplication>
#include <QPixmap>
#include <QSplashScreen>

/*
 * mian函数，程序的入口
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPixmap pixmap;
    pixmap.load(":/images/splash02.png");
    pixmap.scaled(QSize(1200,701));
    QSplashScreen splash(pixmap);
    splash.show();
    a.processEvents();

    MainWindow w;
    w.show();

    splash.finish(&w);
    return a.exec();
}

