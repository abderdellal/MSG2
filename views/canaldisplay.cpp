#include "canaldisplay.h"
#include "imagecontroller.h"
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QDebug>

CanalDisplay::CanalDisplay(QString CANAL, Image * img, QWidget *parent):
    QWidget(parent)
{
    canal = CANAL;
    image = img;
    offsetX = 0;
    offsetY = 0;

    QVBoxLayout * Vlayout = new QVBoxLayout();
    QHBoxLayout * Hlayout1 = new QHBoxLayout();
    QHBoxLayout * Hlayout2 = new QHBoxLayout();

    labelType = new QLabel(canal);
    bouttonModifier = new QPushButton("Découper");
    labelImage = new RedDotLabel();
    labelImage->setMaximumWidth(CanalDisplay::canalWidth);
    labelImage->setMaximumHeight((CanalDisplay::canalWidth * img->getHeight()) /img->getWidth());
    labelCouleur = new QLabel("Couleur");
    couleurEdit = new QLineEdit();
    couleurEdit->setMaximumWidth(50);

    Hlayout1->addWidget(labelType);
    Hlayout1->addWidget(bouttonModifier);
    Hlayout2->addWidget(labelCouleur);
    Hlayout2->addWidget(couleurEdit);
    Vlayout->addLayout(Hlayout1);
    Vlayout->addWidget(labelImage);
    Vlayout->addLayout(Hlayout2);
    Display();
    if(img->getWidth() != 3712 && img->getHeight() != 3712)
    {
        bouttonModifier->setVisible(false);
    }
    else
    {
        bouttonModifier->setVisible(true);
    }
    QObject::connect(labelImage, SIGNAL(clicked(int,int)), this, SLOT(prevenireSignal(int,int)));
    QObject::connect(bouttonModifier, SIGNAL(released()), this, SLOT(modifImage()));

    this->setLayout(Vlayout);
}
CanalDisplay::~CanalDisplay()
{
    delete image;
    delete pixmap;
}

void CanalDisplay::Display()
{
    QImage * qimage = ImageController::getQImage(image);
    pixmap = new QPixmap();
    pixmap->convertFromImage(*qimage);

    delete qimage;

    labelImage->setPixmap(pixmap);
    labelImage->repaint();
}

void CanalDisplay::Display(Image * img, QString CANAL)
{
    image = img;
    canal = CANAL;
    Display();
}

void CanalDisplay::prevenireSignal(int x, int y)
{
    if(image != NULL)
    {
        int X = ((double)(x * image->getWidth())) / labelImage->geometry().width();
        int Y = ((double)(y * image->getHeight())) / labelImage->geometry().height();
        emit PixelSelected(X,Y);
    }
}

void CanalDisplay::selectPixel(int ligne, int cologne)
{
    int y = ((ligne * labelImage->geometry().height()) /image->getHeight() );
    int x =((cologne * labelImage->geometry().width()) /image->getWidth() );
    int color = image->getIntPixel(ligne, cologne);

    char s[100];
    sprintf(s, "%d", color);

    couleurEdit->setText(s);

    labelImage->setX(x + 1);
    labelImage->setY(y + 1);
    labelImage->setDrawing(true);
    labelImage->update();
}

void CanalDisplay::modifImage()
{
    fen = new DecoupeImage();
    QObject::connect(fen, SIGNAL(decouper(int,int,int,int)), this, SLOT(decoup(int,int,int,int)));

    fen->setPixmap(pixmap);
    fen->afficher();
}

void CanalDisplay::decoup(int x1, int y1, int x2, int y2)
{
    emit decouper(x1, y1, x2, y2);
}

void CanalDisplay::displayALL()
{
    labelImage->displayAll();
}

void CanalDisplay::setOffsetX(int ox)
{
    offsetX = ox;
    labelImage->setOffsetX(ox);
}
void CanalDisplay::setOffsetY(int oy)
{
    offsetY = oy;
    labelImage->setOffsetY(oy);
}
