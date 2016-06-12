#include "rvbdisplay.h"
#include "imagecontroller.h"
#include "db.h"
#include <QGridLayout>
#include <QFileDialog>

RVBDisplay::RVBDisplay(QWidget *parent) :
    QWidget(parent)
{
    img = NULL;
    img2 = NULL;
    img3 = NULL;
    rv = false;
    rvb = false;
    offsetX = 0;
    offsetY = 0;
    prepareInterface();
}


RVBDisplay::RVBDisplay(Image * img, Image *img2, Image *img3)
{
    rvb = true;
    rv = true;
    this->img = img;
    this->img2 = img;
    this->img3 = img;

    this->offsetX = img->getOffsetX();
    this->offsetY = img->getOffsetY();
    prepareInterface();

    if(img->getWidth() == img2->getWidth() && img->getWidth() == img3->getWidth() && img->getHeight() == img2->getHeight() && img->getHeight() == img3->getHeight())
        if(img->getOffsetX() == img2->getOffsetX() && img->getOffsetX() == img3->getOffsetX() && img->getOffsetY() == img2->getOffsetY() && img->getOffsetY()== img3->getOffsetY())
        {
            displayImage(img);
        }
}


RVBDisplay::~RVBDisplay()
{
    if(img) delete img;
    if(img2) delete img2;
    if(img3) delete img3;
    if(pixmap)  delete pixmap;
}

void RVBDisplay::prepareInterface()
{
    pixmap = NULL;
    area = NULL;
    Vlayout = new QVBoxLayout;
    QHBoxLayout * Hlayout = new QHBoxLayout;
    QHBoxLayout * Hlayout2 = new QHBoxLayout;

    QIcon iconeRed("Red.png");
    QIcon iconeBleu("Bleu.png");
    QIcon iconeGreen("Green.png");
    bouttonOuvrir1 = new QPushButton(iconeRed, "Rouge");
    bouttonOuvrir2 = new QPushButton(iconeGreen, "Vert");
    bouttonOuvrir3 = new QPushButton(iconeBleu,"Bleu");
    bouttonOuvrir2->setVisible(false);
    bouttonOuvrir3->setVisible(false);
    QIcon iconeZoumIn("zoomin.png");
    QIcon iconeZoumOut("zoomout.png");
    QIcon iconeNegatif("negatif.png");
    QIcon iconeNormalSize("normalSize.png");
    QIcon iconeContrast("contrast.png");
    QIcon iconeStats("stats.png");
    bouttonZoumIn = new QPushButton(iconeZoumIn,"Zoum In");
    bouttonZoumOut = new QPushButton(iconeZoumOut, "Zoum Out");
    bouttonNormalSize = new QPushButton(iconeNormalSize,"Normal Size");
    bouttonNegatif = new QPushButton(iconeNegatif ,"negatif");
    bouttonContrast = new QPushButton(iconeContrast, "Contrast statique");
    bouttonStatistique = new QPushButton(iconeStats, "statistique");
    bouttonZoumIn->setVisible(false);
    bouttonZoumOut->setVisible(false);
    bouttonNormalSize->setVisible(false);
    bouttonNegatif->setVisible(false);
    bouttonContrast->setVisible(false);
    bouttonStatistique->setVisible(false);
    labelColor = new QLabel("Red : /1024");
    editColor = new QLineEdit();
    labelColor256 =  new QLabel("/256");
    editColor256 = new QLineEdit();
    editColor->setMaximumWidth(40);
    editColor256->setMaximumWidth(40);
    labelColorgreen = new QLabel("Green : /1024");
    editColorgreen = new QLineEdit();
    labelColor256green =  new QLabel("/256");
    editColor256green = new QLineEdit();
    editColorgreen->setMaximumWidth(40);
    editColor256green->setMaximumWidth(40);
    labelColorbleu = new QLabel("Bleu : /1024");
    editColorbleu = new QLineEdit();
    labelColor256bleu =  new QLabel("/256");
    editColor256bleu = new QLineEdit();
    editColorbleu->setMaximumWidth(40);
    editColor256bleu->setMaximumWidth(40);
    locationWidget = new LocationWidget();
    communeSelection = new CommuneSelection();
    QIcon iconeAlgerie("algeria.png");
    bouttonDisplayAll = new QPushButton(iconeAlgerie, "tout Selectionner");
    bouttonDisplayAll->setVisible(false);

    Hlayout->addWidget(bouttonOuvrir1);
    Hlayout->addWidget(bouttonOuvrir2);
    Hlayout->addWidget(bouttonOuvrir3);
    Hlayout->addSpacing(10);
    Hlayout->addWidget(bouttonZoumIn);
    Hlayout->addWidget(bouttonZoumOut);
    Hlayout->addWidget(bouttonNormalSize);
    Hlayout->addWidget(bouttonNegatif);
    Hlayout->addWidget(bouttonContrast);
    Hlayout->addWidget(bouttonStatistique);
    Hlayout->addWidget(labelColor);
    Hlayout->addWidget(editColor);
    Hlayout->addWidget(labelColor256);
    Hlayout->addWidget(editColor256);

    Hlayout->addWidget(labelColorgreen);
    Hlayout->addWidget(editColorgreen);
    Hlayout->addWidget(labelColor256green);
    Hlayout->addWidget(editColor256green);

    Hlayout->addWidget(labelColorbleu);
    Hlayout->addWidget(editColorbleu);
    Hlayout->addWidget(labelColor256bleu);
    Hlayout->addWidget(editColor256bleu);

    Hlayout2->addWidget(locationWidget);
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
    QObject::connect(bouttonOuvrir1, SIGNAL(clicked()), this, SLOT(OuvrirFichier1()));
    QObject::connect(bouttonOuvrir2, SIGNAL(clicked()), this, SLOT(OuvrirFichier2()));
    QObject::connect(bouttonOuvrir3, SIGNAL(clicked()), this, SLOT(OuvrirFichier3()));
    QObject::connect(bouttonNegatif, SIGNAL(clicked()), this, SLOT(negatif()));
    QObject::connect(bouttonContrast, SIGNAL(clicked()), this, SLOT(contrast()));
    QObject::connect(bouttonStatistique, SIGNAL(clicked()), this, SLOT(stats()));


    this->setLayout(Vlayout);
}

void RVBDisplay::OuvrirFichier1()
{
    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", ".\\images");
    if (!fichier.isNull())
    {
        offsetX = 0;
        offsetY = 0;
        displayImage(fichier);
        bouttonOuvrir2->setVisible(true);
    }
}

void RVBDisplay::OuvrirFichier2()
{
    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", ".\\images");
    if (!fichier.isNull())
    {
        offsetX = 0;
        offsetY = 0;
        img2 = new Image(fichier);
        if(img->getWidth() ==  img2->getWidth())
        {
            rv = true;
            displayImage(img);
            bouttonOuvrir3->setVisible(true);
        }
    }
}

void RVBDisplay::OuvrirFichier3()
{
    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", ".\\images");
    if (!fichier.isNull())
    {
        offsetX = 0;
        offsetY = 0;
        img3 = new Image(fichier);
        if(img->getWidth() ==  img3->getWidth())
        {
            rvb = true;
            displayImage(img);
        }
    }
}

void RVBDisplay::displayImage(QString fichier)
{
    displayImage(new Image(fichier));
}

void RVBDisplay::displayImage(Image * image)
{
    if(area)
    {
        delete area;
    }

    if(pixmap)  delete pixmap;
    QImage * qimage;

    if(rvb)
    {
        img = image;
        qimage = ImageController::getQImage(img, img2, img3);
    }
    else if(rv)
    {
        img = image;
        qimage = ImageController::getQImage(img, img2);
    }
    else
    {
        if(img) delete img;
        img = image;
        qimage = ImageController::getQImage(img);
    }

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
    bouttonStatistique->setVisible(false);
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

void RVBDisplay::updateCoordonate(int colomn, int line)
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

    int colorgreen = img2->getIntPixel(line, colomn);
    QString sColorgreen;
    sColorgreen.setNum(colorgreen);
    editColorgreen->setText(sColorgreen);
    QString sColor256green;
    sColor256green.setNum(colorgreen/4);
    editColor256green->setText(sColor256green);

    int colorbleu = img3->getIntPixel(line, colomn);
    QString sColorbleu;
    sColorbleu.setNum(colorbleu);
    editColorbleu->setText(sColorbleu);
    QString sColor256bleu;
    sColor256bleu.setNum(colorbleu/4);
    editColor256bleu->setText(sColor256bleu);

}

void RVBDisplay::negatif()
{
    Image * newImage;

    if(rv)
    {
        newImage = img2->negatif();
        delete img2;
        img2 = newImage;
    }
    if(rvb)
    {
        newImage = img3->negatif();
        delete img3;
        img3 = newImage;
    }

     newImage = img->negatif();
     delete img;
     img = NULL;
     displayImage(newImage);
}

void RVBDisplay::contrast()
{
    Image * newImage;

    if(rv)
    {
        newImage = img2->contrastStatique();
        delete img2;
        img2 = newImage;
    }
    if(rvb)
    {
        newImage = img3->contrastStatique();
        delete img3;
        img3 = newImage;
    }

    newImage = img->contrastStatique();
    delete img;
    img = NULL;
    displayImage(newImage);
}

void RVBDisplay::stats()
{
    ChartView * chartView = new ChartView(img);
    chartView->showMaximized();
}
