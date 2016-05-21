#include "decoupage.h"

Decoupage::Decoupage(int id, QString nom, int debX, int debY, int width, int height, QString jour, QString heure, QString quartDheur, QString dateCreated)
{
    this->id = id;
    this->nom = nom;
    this->debX = debX;
    this->debY = debY;
    this->width = width;
    this->height = height;
    this->jour = jour;
    this->heure = heure;
    this->quartDheur = quartDheur;
    this->dateCreated = dateCreated;
}
