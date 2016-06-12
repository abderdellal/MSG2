#ifndef CORRELATIONVIEW_H
#define CORRELATIONVIEW_H

#include <QWidget>
#include <QLabel>
#include "image.h"
#include <QGridLayout>
#include <QDebug>
#include <QPushButton>

class CorrelationView : public QWidget
{
    Q_OBJECT
public:
    explicit CorrelationView(std::map<QString, Image *> imagesMap, QWidget *parent = 0);
    
signals:
    
public slots:
    
};

#endif // CORRELATIONVIEW_H
