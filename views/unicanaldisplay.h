#ifndef UNICANALDISPLAY_H
#define UNICANALDISPLAY_H

#include "scrollreddotlabel.h"
#include "locationwidget.h"
#include "image.h"
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QImage>
#include <QVBoxLayout>
#include <QLineEdit>


class UniCanalDisplay : public QWidget
{
    Q_OBJECT
public:
    explicit UniCanalDisplay(QWidget *parent = 0);
    ~UniCanalDisplay();

private:
    QVBoxLayout * Vlayout;
    QPushButton * bouttonOuvrir;
    QPushButton * bouttonZoumIn;
    QPushButton * bouttonZoumOut;
    QLabel * labelFichier;
    QLineEdit * editColor;
    QLabel * labelColor;
    LocationWidget * locationWidget;
    ScrollRedDotLabel * area;
    Image * img;
    QPixmap * pixmap;
    
signals:
    
public slots:
    void OuvrirFichier();
    void updateCoordonate(int colomn ,int line);
};

#endif // UNICANALDISPLAY_H
