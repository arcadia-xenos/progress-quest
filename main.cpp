#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{

    /*
      This block produced by qt creator for manageing ui
    */
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    // start event loop
    return a.exec();
}

