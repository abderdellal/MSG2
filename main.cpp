#include <QtGui/QApplication>
#include <iostream>
#include <QSqlDatabase>
#include <QDebug>
#include "mainwindow.h"
#include "db.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    if(!DB::connect())
    {
        std::cout << "impossible de se connecter a la base de données";
        return 0;
    }

    w.showMaximized();
    
    return a.exec();
}
