#ifndef DECOUPAGE_H
#define DECOUPAGE_H

#include <QString>

class Decoupage
{
public:
    Decoupage(int id, QString nom, int debX, int debY, int width, int height, QString jour, QString heure, QString quartDheur, QString dateCreated);

    int id;
    QString nom;
    int debX;
    int debY;
    int width;
    int height;
    QString jour;
    QString heure;
    QString quartDheur;
    QString dateCreated;
};

#endif // DECOUPAGE_H
