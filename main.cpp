#include <QtGlobal>

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)

#include <QApplication>

#else

#include <QtGui/QApplication>

#endif

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

