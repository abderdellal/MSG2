#ifndef MultiCanalDisplay_H
#define MultiCanalDisplay_H

#include "locationwidget.h"
#include "imagesselectwidget.h"
#include "image.h"
#include "canaldisplay.h"
#include "communeselection.h"
#include <QWidget>
#include <QGridLayout>
#include <QScrollArea>


class MultiCanalDisplay : public QWidget
{
    Q_OBJECT
public:
    explicit MultiCanalDisplay(QWidget *parent = 0);
    void afficherImage();
    void propagerSignal(int x, int y);
    void setOffsetX(int ox);
    void setOffsetY(int oy);
    void setDossier(QString s);
    void setFinF(QString s);

private:
    QString dossier;
    QString finF;            //la fin des fichier a afficher qui represente l'heure et la minute
    QString canal;            //canal a afficher
    std::map<QString, Image *> imagesMap;
    std::list<CanalDisplay *> widgetsList;

    LocationWidget * locationWidget;
    ImagesSelectWidget * selectionWidget;
    CommuneSelection * communeSelection;
    QGridLayout * Glayout;
    QWidget * centralWidget;
    QScrollArea * area;

    int offsetX;
    int offsetY;
    
signals:
    
public slots:
    void selectFolder(QString folder, QString finFichier);
    void ChangeCoordinate(int x, int y);
    void decoupeImages(int x1, int y1, int x2, int y2);
};

#endif // MultiCanalDisplay_H
