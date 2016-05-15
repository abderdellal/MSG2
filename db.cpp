#include "db.h"
#include <QDebug>

DB::DB()
{
}
QSqlDatabase DB::db;

bool DB::connect()
{
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};FIL={MS Access};DBQ=MSG.accdb");
    if (db.open()) {
        qDebug() << "connected";
        return true;
    }
    else
    {
        qDebug() << "NOT connected";
        return false;
    }
}
