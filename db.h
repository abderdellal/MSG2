#ifndef DB_H
#define DB_H

#include <QSqlDatabase>
#include <QStringList>
#include <QDebug>
#include <QSqlError>
#include <QStringList>
#include <QSqlQuery>
#include <QSqlRecord>
class LatLonPair
{
public:
    double lat;
    double lon;
    LatLonPair(double lt, double ln)
    {
         lat = lt;
         lon = ln;
    }

};


class DB
{
public:
    DB();
    static bool connect();
    static QStringList getCommunes(QString wilaya);
    static QStringList getWilayas();
    static void getLatLon(QString commune, QString wilaya, double &lat, double &lon);
    static std::list<LatLonPair> getAllLatLon();

private:
    static QSqlDatabase db;
};

#endif // DB_H
