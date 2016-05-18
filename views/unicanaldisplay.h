#ifndef UNICANALDISPLAY_H
#define UNICANALDISPLAY_H

#include "scrollreddotlabel.h"
#include "locationwidget.h"
#include "image.h"
#include "communeselection.h"
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QImage>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QComboBox>


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
    QPushButton * bouttonNormalSize;
    QLabel * labelFichier;
    QLineEdit * editColor;
    QLabel * labelColor;
    LocationWidget * locationWidget;
    CommuneSelection * communeSelection;
    QPushButton * bouttonDisplayAll;
    //QLabel * labelWilaya;
    //QComboBox * comboWilaya;
    //QLabel * labelCommune;
    //QComboBox * comboCommune;
    //QPushButton * communeBoutton;
    ScrollRedDotLabel * area;
    Image * img;
    QPixmap * pixmap;

    //void populateComboWilaya();
    
signals:
    
public slots:
    void OuvrirFichier();
    void updateCoordonate(int colomn ,int line);
    //void populateComboCommune(QString wilaya);
    //void selectCommune();
};

#endif // UNICANALDISPLAY_H
