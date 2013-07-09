#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
   QCoreApplication::setOrganizationName("Heaven Inc.");
   QCoreApplication::setOrganizationDomain("adonai.com");
   QCoreApplication::setApplicationName("Life of Game");

    QApplication a(argc, argv);
    a.setAttribute(Qt::AA_SynthesizeTouchForUnhandledMouseEvents, false);
    a.setAttribute(Qt::AA_SynthesizeMouseForUnhandledTouchEvents, false);
    //a.testAttribute(Qt::AA_SynthesizeTouchForUnhandledMouseEvents);

    MainWindow w;
    w.showMaximized();
    
    return a.exec();
}
