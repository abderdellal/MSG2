#include "multicanalcontroller.h"
#include "imagecontroller.h"
#include <QDirIterator>
#include <QMessageBox>

MultiCanalController::MultiCanalController()
{
}
QList<QString> MultiCanalController::getTypesList()
{
    QList<QString> list;
    list << "IR_016" << "IR_039" << "IR_087" << "IR_097" << "IR_108" << "IR_120" << "IR_134" << "VIS006" << "VIS008";
    return list;
}

QMap<QString, Image *> MultiCanalController::getImagesList(QString dossier, QString fin)
{
    QMap<QString, Image *> map;
    QList<QString> listTypes = getTypesList();

    QDirIterator it(dossier);
    QString jour = dossier.section('\\', -1);
    do
    {
        it.next();
        QString fichier = it.fileName();

        if (fichier.contains(jour) && fichier.endsWith(fin + ".pgm"))
        {
            foreach(QString type, listTypes)
            {
                if(fichier.startsWith(type))
                {
                    Image * image = ImageController::getImage(it.filePath());
                    map.insert(type, image);
                }
            }
        }
    }while(it.hasNext());
    return map;
}


