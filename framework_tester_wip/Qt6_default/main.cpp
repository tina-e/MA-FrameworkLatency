#include "mainwindow.h"
#include <QApplication>
#include <windows.h>

QPalette pal = QPalette();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.setWindowTitle("framework");

    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, Qt::black);
    w.setAutoFillBackground(true);
    w.setPalette(pal);

    //w.showFullScreen();
    w.show();
    return a.exec();
}

