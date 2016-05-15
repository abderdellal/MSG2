#ifndef SCROLLREDDOTLABEL_H
#define SCROLLREDDOTLABEL_H

#include "reddotlabel.h"
#include <QMainWindow>
#include <QLabel>
#include <QScrollArea>
#include <QScrollBar>

class ScrollRedDotLabel : public QWidget
{
    Q_OBJECT

public:
    ScrollRedDotLabel(QWidget * parent = 0);
    void setPixmap(QPixmap * p);

private:
    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);

    RedDotLabel *imageLabel;
    QScrollArea *scrollArea;
    double scaleFactor;
    bool ZoomInBool;
    bool ZoomOutBool;

signals:
    void clicked(int x, int y);

public slots:
    void zoomIn();
    void zoomOut();
    void normalSize();
    void emitClick(int x, int y);
    void updateCoordinate(int cologne, int ligne);
};

#endif // SCROLLREDDOTLABEL_H


