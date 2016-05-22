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
    UniCanalDisplay(QString fichier, QWidget *parent = 0);
    UniCanalDisplay(QString fichier, int offsetX, int offsetY ,QWidget *parent = 0);
    ~UniCanalDisplay();
    void prepareInterface();

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

    ScrollRedDotLabel * area;
    Image * img;
    QPixmap * pixmap;

    int offsetX;
    int offsetY;
    
signals:
    
public slots:
    void OuvrirFichier();
    void updateCoordonate(int colomn ,int line);
    void displayImage(QString fichier);
};

#endif // UNICANALDISPLAY_H
