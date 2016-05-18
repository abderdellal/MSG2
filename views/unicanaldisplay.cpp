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
    area = NULL;
    Vlayout = new QVBoxLayout;
    QHBoxLayout * Hlayout = new QHBoxLayout;
    QHBoxLayout * Hlayout2 = new QHBoxLayout;

    bouttonOuvrir = new QPushButton("Ouvrire un fichier");
    labelFichier = new QLabel();
    bouttonZoumIn = new QPushButton("Zoum In");
    bouttonZoumOut = new QPushButton("Zoum Out");
    bouttonNormalSize = new QPushButton("Normal Size");
    bouttonZoumIn->setVisible(false);
    bouttonZoumOut->setVisible(false);
    bouttonNormalSize->setVisible(false);
    labelColor = new QLabel("Color ");
    editColor = new QLineEdit();
    editColor->setMaximumWidth(40);
    locationWidget = new LocationWidget();
    communeSelection = new CommuneSelection();
    bouttonDisplayAll = new QPushButton("Afficher toutes les communes");
    bouttonDisplayAll->setVisible(false);

    Hlayout->addWidget(bouttonOuvrir);
    QIcon icone;
    icone.addFile(QString::fromUtf8("dossier-image-icone-4032-32.png"), QSize(), QIcon::Normal, QIcon::Off);
    bouttonOuvrir->setIcon(icone);
    Hlayout->addWidget(labelFichier);
    Hlayout->addSpacing(100);
    Hlayout->addWidget(bouttonZoumIn);
    Hlayout->addWidget(bouttonZoumOut);
    Hlayout->addWidget(bouttonNormalSize);
    Hlayout2->addWidget(locationWidget);
    Hlayout2->addWidget(labelColor);
    Hlayout2->addWidget(editColor);
    Hlayout2->addWidget(communeSelection);
    Hlayout2->addWidget(bouttonDisplayAll);
    Hlayout->addStretch();
    Hlayout2->addStretch();
    Vlayout->addLayout(Hlayout);
    Vlayout->addLayout(Hlayout2);
    Vlayout->setAlignment(Hlayout, Qt::AlignJustify);
    Vlayout->setAlignment(Hlayout2, Qt::AlignJustify);
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
        if(area)
        {
            delete area;
        }

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
    bouttonZoumIn->setVisible(true);
    bouttonZoumOut->setVisible(true);
    bouttonNormalSize->setVisible(true);
    bouttonDisplayAll->setVisible(true);
    QObject::connect(bouttonZoumIn, SIGNAL(clicked()), area, SLOT(zoomIn()));
    QObject::connect(bouttonZoumOut, SIGNAL(clicked()), area, SLOT(zoomOut()));
    QObject::connect(bouttonNormalSize,SIGNAL(clicked()), area, SLOT(normalSize()));
    QObject::connect(area, SIGNAL(clicked(int,int)), this, SLOT(updateCoordonate(int,int)));
    QObject::connect(locationWidget, SIGNAL(coordinateChanged(int,int)), this, SLOT(updateCoordonate(int,int)));
    QObject::connect(communeSelection, SIGNAL(communeSelected(double,double)), locationWidget, SLOT(ChangeLatLong(double,double)));
    QObject::connect(bouttonDisplayAll, SIGNAL(clicked()), area, SLOT(displayAll()));
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
