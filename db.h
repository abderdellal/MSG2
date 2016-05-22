#ifndef DB_H
#define DB_H

#include <QSqlDatabase>
#include <QStringList>
#include <QDebug>
#include <QString>
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
    static int saveDecoupage(QString nom, int debX, int debY, int width, int height, QString jour, QString heure, QString quartDheur, QString cheminDecoupage);
    static bool saveImage(int decoupageID, QString canal, QString chemin);
    static bool supprDecoupage(int decoupageID, QString chemin = QString());
    static bool supprImage(int ID, QString fichier);
    QSqlDatabase getDB();

private:
    static QSqlDatabase db;
};

#endif // DB_H
