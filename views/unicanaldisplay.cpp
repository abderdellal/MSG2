#include "unicanaldisplay.h"
#include "imagecontroller.h"
#include "db.h"
#include <QGridLayout>
#include <QFileDialog>

UniCanalDisplay::UniCanalDisplay(QWidget *parent) :
    QWidget(parent)
{
    img = NULL;
    pixmap = NULL;
    Vlayout = new QVBoxLayout;
    QHBoxLayout * Hlayout = new QHBoxLayout;
    bouttonOuvrir = new QPushButton("Ouvrire un fichier");
    labelFichier = new QLabel();
    bouttonZoumIn = new QPushButton("Zoum In");
    bouttonZoumOut = new QPushButton("Zoum Out");
    labelColor = new QLabel("Color ");
    editColor = new QLineEdit();
    editColor->setMaximumWidth(40);
    locationWidget = new LocationWidget();
    communeSelection = new CommuneSelection();

    Hlayout->addWidget(bouttonOuvrir);
    Hlayout->addWidget(labelFichier);
    Hlayout->addWidget(bouttonZoumIn);
    Hlayout->addWidget(bouttonZoumOut);
    Hlayout->addWidget(labelColor);
    Hlayout->addWidget(editColor);
    Hlayout->addWidget(locationWidget);
    Hlayout->addWidget(communeSelection);
    Hlayout->setMargin(0);
    Vlayout->addLayout(Hlayout);
    Vlayout->setMargin(0);

    QObject::connect(bouttonOuvrir, SIGNAL(clicked()), this, SLOT(OuvrirFichier()));
    this->setLayout(Vlayout);
}

UniCanalDisplay::~UniCanalDisplay()
{
    if(img) delete img;
    if(pixmap)  delete pixmap;
}

void UniCanalDisplay::OuvrirFichier()
{
    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", ".\\images");
    if (!fichier.isNull())
    {
    if(img) delete img;
    if(pixmap)  delete pixmap;
    labelFichier->setText(fichier.section("/",-1));
    img = new Image(fichier);
    QImage * qimage = ImageController::getQImage(img);
    pixmap = new QPixmap();
    pixmap->convertFromImage(*qimage);
    delete qimage;
    area = new ScrollRedDotLabel();
    area->setPixmap(pixmap);
    Vlayout->addWidget(area);
    QObject::connect(bouttonZoumIn, SIGNAL(clicked()), area, SLOT(zoomIn()));
    QObject::connect(bouttonZoumOut, SIGNAL(clicked()), area, SLOT(zoomOut()));
    QObject::connect(area, SIGNAL(clicked(int,int)), this, SLOT(updateCoordonate(int,int)));
    QObject::connect(locationWidget, SIGNAL(coordinateChanged(int,int)), this, SLOT(updateCoordonate(int,int)));
    QObject::connect(communeSelection, SIGNAL(communeSelected(double,double)), locationWidget, SLOT(ChangeLatLong(double,double)));
    }
}

void UniCanalDisplay::updateCoordonate(int colomn, int line)
{
    locationWidget->displayCoordinate(colomn, line);
    area->updateCoordinate(colomn, line);
    int color = img->getIntPixel(line, colomn);
    QString sColor;
    sColor.setNum(color);
    editColor->setText(sColor);
}
