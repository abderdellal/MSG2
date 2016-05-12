#include "reddotlabel.h"

RedDotLabel::RedDotLabel(QWidget *parent) :
    QLabel(parent)
{
    drawing = false;
    x = 0;
    y = 0;

    this->setScaledContents(true);
}

RedDotLabel::RedDotLabel(int w, int h, QWidget *parent) :
    QLabel(parent)
{
    drawing = false;
    x = 0;
    y = 0;

    this->setScaledContents(true);
    this->setMaximumWidth(w);
    this->setMaximumHeight(h);
}

void RedDotLabel::setpixmap(QPixmap * p)
{
    pixmap = p;
    QLabel::setPixmap(*p);
}

void RedDotLabel::RedDotLabel::resizeEvent(QResizeEvent *)
{
    QPixmap scaledPix = pixmap->scaled(400, 400,   Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QLabel::setPixmap(scaledPix);
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

