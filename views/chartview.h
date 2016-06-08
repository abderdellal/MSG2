#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QWidget>
#include <QVector>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include "qcustomplot.h"
#include "image.h"

class ChartView : public QWidget
{
    Q_OBJECT
public:
    explicit ChartView(Image *img,QWidget *parent = 0);

private:
    QCustomPlot * customPlot;
    QVector<double> valeurs;
    QVector<double> repets;
    Image * img;

    QLabel * labelMaxCouleur;
    QLabel * labelMinCouleur;
    QLabel * labelMoyenne;
    QLabel * labelVariance;
    QLabel * labelEquarType;

    QLineEdit * editMaxCouleur;
    QLineEdit * editMinCouleur;
    QLineEdit * editMoyenne;
    QLineEdit * editVariance;
    QLineEdit * editEquarType;
    
signals:
    
public slots:
    
};

#endif // CHARTVIEW_H
