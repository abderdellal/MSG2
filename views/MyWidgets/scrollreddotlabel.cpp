#include "scrollreddotlabel.h"
#include <QHBoxLayout>
#include <QDebug>

ScrollRedDotLabel::ScrollRedDotLabel(QWidget * parent):QWidget(parent)
{
    ZoomInBool = true;
    ZoomOutBool = true;
    imageLabel = new RedDotLabel;
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);
    QHBoxLayout * layout = new QHBoxLayout;
    scrollArea = new QScrollArea();
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);
    layout->addWidget(scrollArea);
    layout->setMargin(0);
    this->setLayout(layout);
}


void ScrollRedDotLabel::setPixmap(QPixmap *p)
{
    imageLabel->setPixmap(p);
    scaleFactor = 1.0;
    imageLabel->adjustSize();
    QObject::connect(imageLabel, SIGNAL(clicked(int,int)), this, SLOT(emitClick(int,int)));
}

void ScrollRedDotLabel::emitClick(int x, int y)
{
    int cologne = ((double)(x * imageLabel->getPixmap()->width())) / imageLabel->geometry().width();
    int ligne = ((double)(y * imageLabel->getPixmap()->height())) / imageLabel->geometry().height();
    emit clicked(cologne, ligne);
}

void ScrollRedDotLabel::updateCoordinate(int cologne, int ligne)
{
    int y = ((ligne * imageLabel->geometry().height()) /imageLabel->getPixmap()->height() );
    int x =((cologne * imageLabel->geometry().width()) /imageLabel->getPixmap()->width() );

    imageLabel->setX(x);
    imageLabel->setY(y);
    imageLabel->setDrawing(true);
    imageLabel->update();
}


void ScrollRedDotLabel::zoomIn()
{
    if(ZoomInBool)
    {
        scaleImage(1.25);
    }
}

void ScrollRedDotLabel::zoomOut()
{
    if(ZoomOutBool)
    {
        scaleImage(0.8);
    }
}

void ScrollRedDotLabel::normalSize()
{
    imageLabel->adjustSize();
    scaleFactor = 1.0;
}


void ScrollRedDotLabel::scaleImage(double factor)
{
    if(imageLabel->getPixmap());
    {
        scaleFactor *= factor;
        imageLabel->resize(scaleFactor * imageLabel->getPixmap()->size());

        adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
        adjustScrollBar(scrollArea->verticalScrollBar(), factor);

        ZoomInBool = (scaleFactor < 3.0);
        ZoomOutBool = (scaleFactor > 0.167);
    }
}

void ScrollRedDotLabel::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value()
                            + ((factor - 1) * scrollBar->pageStep()/2)));
}
