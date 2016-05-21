#include "db.h"

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

std::list<LatLonPair> DB::getAllLatLon()
{
    std::list<LatLonPair> list;
    QSqlQuery query("SELECT DISTINCT Latitude, Longitude FROM communes");
    while (query.next())
    {
       double lat = query.value(0).toDouble();
       double lon = query.value(1).toDouble();
       LatLonPair p(lat,lon);
       list.push_back(p);
    }
    return list;
}

int DB::saveDecoupage(QString nom, int debX, int debY, int width, int height, QString jour, QString heure, QString quartDheur, QString cheminDecoupage)
{
    QSqlQuery query;
    query.prepare("INSERT INTO decoupages (nom, x, y, width, height, jour, heure, quartDheur, chemin ) VALUES (:nom, :x, :y, :width, :height, :jour, :heure, :quartDheur, :chemin)");
    query.bindValue(0, nom);
    query.bindValue(1, debX);
    query.bindValue(2, debY);
    query.bindValue(3, width);
    query.bindValue(4, height);
    query.bindValue(5, jour);
    query.bindValue(6, heure);
    query.bindValue(7, quartDheur);
    query.bindValue(8, cheminDecoupage);
    query.exec();
    int id = query.lastInsertId().value<int>();
    return id;
}

bool DB::saveImage(int decoupageId, QString canal, QString chemin)
{
    QSqlQuery query;
    query.prepare("INSERT INTO images (decoupageId, canal, chemin) VALUES (:decoupageId, :canal, :chemin)");
    query.bindValue(":decoupageId", decoupageId);
    query.bindValue(":canal", canal);
    query.bindValue(":chemin", chemin);
    bool ok = query.exec();
    return ok;
}

QSqlDatabase DB::getDB()
{
    return db;
}
