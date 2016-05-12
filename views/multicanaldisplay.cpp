#include "multicanaldisplay.h"
#include "multicanalcontroller.h"
#include "canaldisplay.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QDir>

MultiCanalDisplay::MultiCanalDisplay(QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout *Vlayout = new QVBoxLayout();
    QHBoxLayout * Hlayout = new QHBoxLayout();
    Glayout = new QGridLayout();

    locationWidget = new LocationWidget();
    selectionWidget = new ImagesSelectWidget();
    Hlayout->addWidget(selectionWidget);
    Hlayout->addWidget(locationWidget);


    centralWidget = new QWidget();
    area = new QScrollArea();
    area->setWidgetResizable(true);
    area->setWidget(centralWidget);
    centralWidget->setLayout(Glayout);

    Vlayout->addLayout(Hlayout);
    Vlayout->addWidget(area);

    this->setLayout(Vlayout);

    QObject::connect(selectionWidget, SIGNAL(folderSelected(QString,QString)), this, SLOT(selectFolder(QString,QString)));
}

void MultiCanalDisplay::selectFolder(QString folder, QString finFichier)
{
    finF = finFichier;
    dossier = folder;
    afficherImage();
}

using namespace std;
void MultiCanalDisplay::afficherImage()
{

    foreach(CanalDisplay * display, widgetsList)
    {
        Glayout->removeWidget(display);
        delete display;
    }
    widgetsList.clear();
    imagesMap.clear();

    QMap<QString, Image *> map = MultiCanalController::getImagesList(dossier, finF);
    imagesMap = map.toStdMap();
    std::map<QString, Image *>::iterator it;
    int j = 0;
    for(it = imagesMap.begin() ; it != imagesMap.end() ; ++it)
    {
        QString s = it->first;
        Image * img = it->second;
        CanalDisplay * display = new CanalDisplay(s, img);
        widgetsList.push_back(display);
        Glayout->addWidget(display, j/3, j%3);
        QObject::connect(display, SIGNAL(PixelSelected(int,int)), this, SLOT(ChangeCoordinate(int,int)));
        QObject::connect(display, SIGNAL(decouper(int,int,int,int)), this, SLOT(decoupeImages(int,int,int,int)));
        QObject::connect(locationWidget, SIGNAL(coordinateChanged(int,int)), this, SLOT(ChangeCoordinate(int,int)));
        repaint();
        j++;
    }
}
void MultiCanalDisplay::ChangeCoordinate(int x, int y)
{
    propagerSignal(x, y);
    locationWidget->displayCoordinate(x, y);
}

void MultiCanalDisplay::propagerSignal(int x, int y)
{
    foreach(CanalDisplay * display, widgetsList)
    {
        display->selectPixel(y, x);
    }
}


void MultiCanalDisplay::decoupeImages(int x1, int y1, int x2, int y2)
{
    std::map<QString, Image *>::iterator it;
    for(it = imagesMap.begin() ; it != imagesMap.end() ; ++it)
    {
        QString type = it->first;
        Image * img = it->second;
        QString filePath = "";
        filePath.append(".\\decoupe\\");
        filePath.append(dossier.section('\\',-1));
        QDir dir(filePath);
        if (!dir.exists()) {
            dir.mkpath(".");
        }
        filePath.append("\\");
        filePath.append(type);
        filePath.append(dossier.section('\\',-1));
        filePath.append(finF);
        int minX = (x1>x2)?x2:x1;
        int maxX = (x1>x2)?x1:x2;
        int minY = (y1>y2)?y2:y1;
        int maxY = (y1>y2)?y1:y2;
        int w = maxX - minX;
        int h = maxY - minY;
        char c[50];
        sprintf(c, "(%d-%d-%d-%d).pgm", minX, minY, w, h);
        filePath.append(c);
        Image * newImg = img->crop(x1, y1, x2, y2);
        newImg->save(filePath);
        delete newImg;
    }
}
