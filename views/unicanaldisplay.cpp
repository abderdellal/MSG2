#include "unicanaldisplay.h"
#include "imagecontroller.h"
#include "db.h"
#include <QGridLayout>
#include <QFileDialog>

UniCanalDisplay::UniCanalDisplay(QWidget *parent) :
    QWidget(parent)
{
    offsetX = 0;
    offsetY = 0;
    prepareInterface();
}

UniCanalDisplay::UniCanalDisplay(QString fichier, QWidget *parent):
    QWidget(parent)
{
    offsetX = 0;
    offsetY = 0;
    prepareInterface();
    displayImage(fichier);
}

UniCanalDisplay::UniCanalDisplay(QString fichier, int offsetX, int offsetY, QWidget *parent)
{
    this->offsetX = offsetX;
    this->offsetY = offsetY;
    prepareInterface();
    displayImage(fichier);
}
UniCanalDisplay::UniCanalDisplay(Image * img)
{
    this->offsetX = img->getOffsetX();
    this->offsetY = img->getOffsetY();
    prepareInterface();
    displayImage(img);
}

UniCanalDisplay::~UniCanalDisplay()
{
    if(img) delete img;
    if(pixmap)  delete pixmap;
}

void UniCanalDisplay::prepareInterface()
{
    img = NULL;
    pixmap = NULL;
    area = NULL;
    Vlayout = new QVBoxLayout;
    QHBoxLayout * Hlayout = new QHBoxLayout;
    QHBoxLayout * Hlayout2 = new QHBoxLayout;

    QIcon iconeFichier("afficher.png");
    bouttonOuvrir = new QPushButton(iconeFichier, "Ouvrire un fichier");
    labelFichier = new QLabel();
    QIcon iconeZoumIn("zoomin.png");
    QIcon iconeZoumOut("zoomout.png");
    QIcon iconeNegatif("negatif.png");
    QIcon iconeNormalSize("normalSize.png");
    QIcon iconeContrast("contrast.png");
    bouttonZoumIn = new QPushButton(iconeZoumIn,"Zoum In");
    bouttonZoumOut = new QPushButton(iconeZoumOut, "Zoum Out");
    bouttonNormalSize = new QPushButton(iconeNormalSize,"Normal Size");
    bouttonNegatif = new QPushButton(iconeNegatif ,"negatif");
    bouttonContrast = new QPushButton(iconeContrast, "Contrast statique");
    bouttonStatistique = new QPushButton("statistique");
    bouttonZoumIn->setVisible(false);
    bouttonZoumOut->setVisible(false);
    bouttonNormalSize->setVisible(false);
    bouttonNegatif->setVisible(false);
    bouttonContrast->setVisible(false);
    bouttonStatistique->setVisible(false);
    labelColor = new QLabel("Couleur : /1024");
    editColor = new QLineEdit();
    labelColor256 =  new QLabel("/256");
    editColor256 = new QLineEdit();
    editColor->setMaximumWidth(40);
    editColor256->setMaximumWidth(40);
    locationWidget = new LocationWidget();
    communeSelection = new CommuneSelection();
    QIcon iconeAlgerie("algeria.png");
    bouttonDisplayAll = new QPushButton(iconeAlgerie, "toutes Selectionner");
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
    Hlayout->addWidget(bouttonNegatif);
    Hlayout->addWidget(bouttonContrast);
    Hlayout->addWidget(bouttonStatistique);
    Hlayout2->addWidget(locationWidget);
    Hlayout2->addWidget(labelColor);
    Hlayout2->addWidget(editColor);
    Hlayout2->addWidget(labelColor256);
    Hlayout2->addWidget(editColor256);
    Hlayout2->addWidget(communeSelection);
    Hlayout2->addWidget(bouttonDisplayAll);
    Hlayout->addStretch();
    Hlayout2->addStretch();
    Vlayout->addLayout(Hlayout);
    Vlayout->addLayout(Hlayout2);
    Vlayout->setAlignment(Hlayout, Qt::AlignJustify);
    Vlayout->setAlignment(Hlayout2, Qt::AlignJustify);
    area = new ScrollRedDotLabel();
    Vlayout->addWidget(area);
    area->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QObject::connect(bouttonOuvrir, SIGNAL(clicked()), this, SLOT(OuvrirFichier()));
    QObject::connect(bouttonNegatif, SIGNAL(clicked()), this, SLOT(negatif()));
    QObject::connect(bouttonContrast, SIGNAL(clicked()), this, SLOT(contrast()));
    QObject::connect(bouttonStatistique, SIGNAL(clicked()), this, SLOT(stats()));


    this->setLayout(Vlayout);
}

void UniCanalDisplay::OuvrirFichier()
{
    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", ".\\images");
    if (!fichier.isNull())
    {
        offsetX = 0;
        offsetY = 0;
        displayImage(fichier);
    }
}

void UniCanalDisplay::displayImage(QString fichier)
{
    labelFichier->setText(fichier.section("/",-1));
    displayImage(new Image(fichier));
}

void UniCanalDisplay::displayImage(Image * image)
{
    if(area)
    {
        delete area;
    }

    if(pixmap)  delete pixmap;
    if(img) delete img;

    img = image;

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
    bouttonNegatif->setVisible(true);
    bouttonContrast->setVisible(true);
    bouttonDisplayAll->setVisible(true);
    bouttonStatistique->setVisible(true);
    QObject::connect(bouttonZoumIn, SIGNAL(clicked()), area, SLOT(zoomIn()));
    QObject::connect(bouttonZoumOut, SIGNAL(clicked()), area, SLOT(zoomOut()));
    QObject::connect(bouttonNormalSize,SIGNAL(clicked()), area, SLOT(normalSize()));
    QObject::connect(area, SIGNAL(clicked(int,int)), this, SLOT(updateCoordonate(int,int)));
    QObject::connect(locationWidget, SIGNAL(coordinateChanged(int,int)), this, SLOT(updateCoordonate(int,int)));
    QObject::connect(communeSelection, SIGNAL(communeSelected(double,double)), locationWidget, SLOT(ChangeLatLong(double,double)));
    QObject::connect(bouttonDisplayAll, SIGNAL(clicked()), area, SLOT(displayAll()));


    locationWidget->setOffsetX(offsetX);
    locationWidget->setOffsetY(offsetY);
    area->setOffsetX(offsetX);
    area->setOffsetY(offsetY);

}

void UniCanalDisplay::updateCoordonate(int colomn, int line)
{
    locationWidget->displayCoordinate(colomn, line);
    area->updateCoordinate(colomn, line);
    int color = img->getIntPixel(line, colomn);
    QString sColor;
    sColor.setNum(color);
    editColor->setText(sColor);
    QString sColor256;
    sColor256.setNum(color/4);
    editColor256->setText(sColor256);
}

void UniCanalDisplay::negatif()
{
    Image * newImage = img->negatif();
    displayImage(newImage);
}

void UniCanalDisplay::contrast()
{
    Image * newImage = img->contrastStatique();
    displayImage(newImage);
}

void UniCanalDisplay::stats()
{
    ChartView * chartView = new ChartView(img);
    chartView->showMaximized();

}
