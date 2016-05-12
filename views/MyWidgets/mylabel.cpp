#include "mylabel.h"

MyLabel::MyLabel(QWidget *parent) :
    QLabel(parent)
{
    this->setScaledContents(true);
}

MyLabel::MyLabel(int w, int h, QWidget *parent) :
    QLabel(parent)
{
    this->setMaximumHeight(h);
    this->setMaximumWidth(w);
    this->setScaledContents(true);
}
