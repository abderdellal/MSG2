#ifndef REDDOTLABEL_H
#define REDDOTLABEL_H

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


private:
    QPixmap * pixmap;
    bool drawing;
    int x;
    int y;
    int w; //width
    int h; //height

protected:
    void mouseReleaseEvent(QMouseEvent * event);
    void paintEvent(QPaintEvent *event);
    void drawPoint(QPainter *qp);
    void resizeEvent(QResizeEvent *);

signals:
    void clicked(int x, int y);
    
};

#endif // REDDOTLABEL_H
