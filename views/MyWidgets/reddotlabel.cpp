#include "reddotlabel.h"
#include "latlong.h"

RedDotLabel::RedDotLabel(QWidget *parent) :
    QLabel(parent)
{
    pixmap = NULL;
    drawing = false;
    drawingAll = false;
    x = 0;
    y = 0;
    w = 0;
    h = 0;
    offsetX = 0;
    offsetY = 0;

    this->setScaledContents(true);
}

RedDotLabel::RedDotLabel(int w, int h, QWidget *parent) :
    QLabel(parent)
{
    drawing = false;
    drawingAll = false;
    x = 0;
    y = 0;
    offsetX = 0;
    offsetY = 0;

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
    if(drawingAll)
    {
        QPainter qp(this);
        drawAllPoints(&qp);
    }
}

void RedDotLabel::drawAllPoints(QPainter * qp)
{
    foreach(LatLonPair p, pointsList)
    {
        double lat = p.lat;
        double lon = p.lon;
        int colomn = 0;
        int line = 0;
        LatLong::Getlinepixel(lat, lon, &line, &colomn);
        line -= 1;
        colomn -= 1;
        line -= offsetY;
        colomn -= offsetX;
        double factor = ((double) this->geometry().height()) /this->getPixmap()->height();
        factor = factor - 1;
        int y = ((line * this->geometry().height()) /this->getPixmap()->height() ) + factor;
        int x =((colomn * this->geometry().width()) /this->getPixmap()->width() ) + factor;
        drawPoint(qp, x, y);
    }
}

void RedDotLabel::drawPoint(QPainter *qp) {

  QPen pen(Qt::red, 3, Qt::SolidLine);
  qp->setPen(pen);
  qp->drawPoint(x, y);
}

void RedDotLabel::drawPoint(QPainter *qp, int xx, int yy) {

  QPen pen(Qt::red, 3, Qt::SolidLine);
  qp->setPen(pen);
  qp->drawPoint(xx, yy);
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


void RedDotLabel::displayAll()
{
    if(drawingAll == false)
    {
        drawingAll = true;
        pointsList = DB::getAllLatLon();
    }
    else
    {
        drawingAll = false;
    }
    update();

}

void RedDotLabel::setOffsetX(int ox)
{
    offsetX = ox;
}

void RedDotLabel::setOffsetY(int oy)
{
    offsetY = oy;
}
