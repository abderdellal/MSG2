#include <QtGui/QApplication>
#include <iostream>
#include <QSqlDatabase>
#include "mainwindow.h"
#include "db.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    DB::connect();

    w.showMaximized();
    
    return a.exec();
}
