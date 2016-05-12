#include "labeldecoupe.h"

LabelDecoupe::LabelDecoupe(QWidget *parent) :
    QLabel(parent)
{
    firstClick = false;
    secondClick = false;
    point1_x = 0;
    point1_y = 0;
    point2_x = 0;
    point2_y = 0;
}

void LabelDecoupe::setPixmap(QPixmap * qp)
{
    QLabel::setPixmap(*qp);
    pixmap = qp;
}

void LabelDecoupe::resizeEvent(QResizeEvent *)
{
    int w = this->width();
    int h = this->height();

    QLabel::setPixmap(pixmap->scaled(w,h,Qt::KeepAspectRatio));

}

void LabelDecoupe::mouseReleaseEvent(QMouseEvent *ev)
{
    if(!firstClick && !secondClick)
    {
        point1_x = ev->x();
        point1_y = ev->y();
        firstClick = true;
        int x = (point1_x * pixmap->width())/this->width();
        int y = (point1_y * pixmap->height())/this->width();
        emit click1(x, y);
    }
    else if (firstClick && !secondClick)
    {
        point2_x = ev->x();
        point2_y = ev->y();
        secondClick = true;
        int x = (point2_x * pixmap->width())/this->width();
        int y = (point2_y * pixmap->height())/this->width();
        emit click2(x, y);
    }
    else if (firstClick && secondClick)
    {
        emit cleared();
        point1_x = ev->x();
        point1_y = ev->y();
        secondClick = false;
        int x = (point1_x * pixmap->width())/this->width();
        int y = (point1_y * pixmap->height())/this->width();
        emit click1(x, y);
    }
    update();
}

void LabelDecoupe::paintEvent(QPaintEvent *ev)
{
    QLabel::paintEvent(ev);
    QPainter qp(this);
    QPen pen(Qt::red, 1, Qt::DashDotDotLine);
    qp.setPen(pen);
    if(firstClick)
    {
        qp.drawLine(point1_x, 0, point1_x, this->height());
        qp.drawLine(0, point1_y, this->width(), point1_y);
    }
    if(secondClick)
    {
        qp.drawLine(point2_x, 0, point2_x, this->height());
        qp.drawLine(0, point2_y, this->width(), point2_y);
    }
}

void LabelDecoupe::setPointX1(int n)
{
    point1_x = n;
}
void LabelDecoupe::setPointY1(int n)
{
    point1_y = n;
}
void LabelDecoupe::setPointX2(int n)
{
    point2_x = n;
}
void LabelDecoupe::setPointY2(int n)
{
    point2_y = n;
}

