#include "db.h"
#include <QDebug>
#include <QSqlError>
#include <QStringList>
#include <QSqlQuery>
#include <QSqlRecord>
DB::DB()
{
}
QSqlDatabase DB::db;

bool DB::connect()
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("MSG.db");
    if (db.open()) {
        return true;
    }
    else
    {
        return false;
    }
}

QStringList DB::getWilayas()
{
    QStringList list;
    QSqlQuery query("SELECT DISTINCT WILAYA FROM communes");
    while (query.next())
    {
       QString wilaya = query.value(0).toString();
       list.append(wilaya);
    }
    return list;
}

QStringList DB::getCommunes(QString wilaya)
{
    QStringList list;
    QSqlQuery query;
    QString s("SELECT DISTINCT COMMUNE FROM communes WHERE WILAYA = '%1'");
    s = s.arg(wilaya);
    query.prepare(s);
    query.exec();
    while (query.next())
    {
       QString commune = query.value(0).toString();
       list.append(commune);
    }
     return list;
}

void DB::getLatLon(QString commune, QString wilaya, double &lat, double &lon)
{
    QSqlQuery query;
    QString s("SELECT Latitude, Longitude FROM communes WHERE WILAYA = '%1' AND COMMUNE='%2' ");
    s = s.arg(wilaya, commune);
    query.prepare(s);
    query.exec();
    query.next();
    lat = query.value(0).toDouble();
    lon = query.value(1).toDouble();
}
