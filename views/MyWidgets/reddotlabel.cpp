#include "reddotlabel.h"

RedDotLabel::RedDotLabel(QWidget *parent) :
    QLabel(parent)
{
    pixmap = NULL;
    drawing = false;
    x = 0;
    y = 0;
    w = 0;
    h = 0;

    this->setScaledContents(true);
}

RedDotLabel::RedDotLabel(int w, int h, QWidget *parent) :
    QLabel(parent)
{
    drawing = false;
    x = 0;
    y = 0;

    this->setScaledContents(true);
    this->w = w;
    this->h = h;
    this->setMaximumWidth(w);
    this->setMaximumHeight(h);
}

QPixmap * RedDotLabel::getPixmap()
{
    return pixmap;
}

void RedDotLabel::setHeight(int h)
{
    this->h = h;
}
void RedDotLabel::setWidth(int w)
{
    this->w = w;
}

void RedDotLabel::setPixmap(QPixmap * p)
{
    pixmap = p;
    QLabel::setPixmap(*p);
}

void RedDotLabel::RedDotLabel::resizeEvent(QResizeEvent *)
{
    if(w != 0 && h != 0)
    {
        QPixmap scaledPix = pixmap->scaled(w, h,   Qt::KeepAspectRatio, Qt::SmoothTransformation);
        QLabel::setPixmap(scaledPix);
    }
}

void RedDotLabel::mouseReleaseEvent( QMouseEvent * event )
{
    int x = event->x();
    int y = event->y();

    emit clicked(x, y);
}

void RedDotLabel::paintEvent(QPaintEvent *e) {

    QLabel::paintEvent(e);

    if(drawing)
    {
        QPainter qp(this);
        drawPoint(&qp);
    }
}

void RedDotLabel::drawPoint(QPainter *qp) {

  QPen pen(Qt::red, 3, Qt::SolidLine);
  qp->setPen(pen);
  qp->drawPoint(x, y);
}

void RedDotLabel::setX(int i)
{
    x = i;
}

void RedDotLabel::setY(int i)
{
    y = i;
}

void RedDotLabel::setDrawing(bool b)
{
    drawing = b;
}

