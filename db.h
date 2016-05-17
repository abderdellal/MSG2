#ifndef DB_H
#define DB_H

#include <QSqlDatabase>
#include <QStringList>

class DB
{
public:
    DB();
    static bool connect();
    static QStringList getCommunes(QString wilaya);
    static QStringList getWilayas();
    static void getLatLon(QString commune, QString wilaya, double &lat, double &lon);

private:
    static QSqlDatabase db;
};

#endif // DB_H
