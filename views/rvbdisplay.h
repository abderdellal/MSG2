#ifndef RVBDISPLAY_H
#define RVBDISPLAY_H

#include "scrollreddotlabel.h"
#include "locationwidget.h"
#include "image.h"
#include "communeselection.h"
#include "chartview.h"
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QImage>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QComboBox>


class RVBDisplay : public QWidget
{
    Q_OBJECT
public:
    explicit RVBDisplay(QWidget *parent = 0);
    RVBDisplay(Image *img, Image * img2, Image * img3);
    ~RVBDisplay();
    void prepareInterface();

private:
    QVBoxLayout * Vlayout;
    QPushButton * bouttonOuvrir1;
    QPushButton * bouttonOuvrir2;
    QPushButton * bouttonOuvrir3;

    QPushButton * bouttonZoumIn;
    QPushButton * bouttonZoumOut;
    QPushButton * bouttonNormalSize;
    QPushButton * bouttonNegatif;
    QPushButton * bouttonContrast;
    QPushButton * bouttonStatistique;
    QLineEdit * editColor;
    QLabel * labelColor;
    QLabel * labelColor256;
    QLineEdit * editColor256;
    QLineEdit * editColorgreen;
    QLabel * labelColorgreen;
    QLabel * labelColor256green;
    QLineEdit * editColor256green;
    QLineEdit * editColorbleu;
    QLabel * labelColorbleu;
    QLabel * labelColor256bleu;
    QLineEdit * editColor256bleu;
    LocationWidget * locationWidget;
    CommuneSelection * communeSelection;
    QPushButton * bouttonDisplayAll;

    ScrollRedDotLabel * area;
    Image * img;
    Image * img2;
    Image * img3;

    QPixmap * pixmap;

    int offsetX;
    int offsetY;

    bool rvb;
    bool rv;

signals:

public slots:
    void OuvrirFichier1();
    void OuvrirFichier2();
    void OuvrirFichier3();
    void updateCoordonate(int colomn ,int line);
    void displayImage(QString fichier);
    void displayImage(Image *image);
    void negatif();
    void contrast();
    void stats();
};

#endif // RVBDISPLAY_H
