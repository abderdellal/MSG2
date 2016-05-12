#ifndef MULTICANALCONTROLLER_H
#define MULTICANALCONTROLLER_H

#include "image.h"
#include <QList>
#include <QMap>

class MultiCanalController
{
public:
    MultiCanalController();
    static QMap<QString, Image *> getImagesList(QString dossier, QString fin);
    static QList<QString> getTypesList();

private:
};

#endif // MULTICANALCONTROLLER_H
