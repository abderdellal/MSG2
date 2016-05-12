#ifndef COORDINATEWIDGET_H
#define COORDINATEWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>


class coordinateWidget : public QWidget
{
    Q_OBJECT
public:
    explicit coordinateWidget(QWidget *parent = 0);
    int getX();
    int getY();
    int setX(QString X);
    int setY(QString Y);

private:
    int x;
    int y;

    QLabel * labelX;
    QLineEdit * editX;
    QLabel * labelY;
    QLineEdit * editY;
    QPushButton * boutton;
    
signals:
    void coordinateChanged(int x, int y);
    
public slots:
    void setXY(int X, int Y);
    void changeCoordinate();
};

#endif // COORDINATEWIDGET_H
