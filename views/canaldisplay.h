#ifndef CANALDISPLAY_H
#define CANALDISPLAY_H

#include "reddotlabel.h"
#include "image.h"
#include "decoupeimage.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class CanalDisplay : public QWidget
{
    Q_OBJECT
public:
    explicit CanalDisplay(QString CANAL, Image * img, QWidget *parent = 0);
    ~CanalDisplay();
    void Display(Image * img, QString CANAL);
    void selectPixel(int ligne, int cologne);
    static const int canalWidth = 400;
    static const int canalHeight = 400;



private:
    void Display();
    QString canal;
    Image * image;
    QPixmap * pixmap;

    QLabel * labelType;
    QPushButton * bouttonModifier;
    RedDotLabel * labelImage;
    QLabel * labelCouleur;
    QLineEdit * couleurEdit;
    DecoupeImage * fen;


signals:
    void PixelSelected(int x, int y);
    void decouper(int x1, int y1, int x2, int y2);

public slots:
    void prevenireSignal(int x, int y);
    void modifImage();
    void decoup(int x1, int y1, int x2, int y2);

};


#endif // CANALDISPLAY_H


