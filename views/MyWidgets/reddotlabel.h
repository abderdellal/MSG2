#ifndef REDDOTLABEL_H
#define REDDOTLABEL_H
#include "db.h"
#include <QLabel>
#include <QPainter>
#include <QMouseEvent>
#include <QColor>

class RedDotLabel : public QLabel
{
    Q_OBJECT
public:
    explicit RedDotLabel(QWidget *parent = 0);
    RedDotLabel(int w, int h, QWidget *parent = 0);
    QPixmap * getPixmap();
    void setPixmap(QPixmap * p);
    void setX(int i);
    void setY(int i);
    void setDrawing(bool b);
    void setWidth(int);
    void setHeight (int);
    void setOffsetX(int ox);
    void setOffsetY(int oy);


private:
    QPixmap * pixmap;
    bool drawing;
    bool drawingAll;
    int x;
    int y;
    int w; //width
    int h; //height
    int offsetX;
    int offsetY;
    std::list<LatLonPair> pointsList;

    void drawAllPoints(QPainter *qp);

protected:
    void mouseReleaseEvent(QMouseEvent * event);
    void paintEvent(QPaintEvent *event);
    void drawPoint(QPainter *qp);
    void drawPoint(QPainter *qp, int xx, int yy);
    void resizeEvent(QResizeEvent *);


signals:
    void clicked(int x, int y);

public slots:
        void displayAll();
    
};

#endif // REDDOTLABEL_H
