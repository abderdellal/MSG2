#ifndef LocationWidget_H
#define LocationWidget_H

#include <QWidget>
#include "coordinatewidget.h"
#include "latlonwidget.h"

class LocationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LocationWidget(QWidget *parent = 0);
    void setOffsetX(int ox);
    void setOffsetY(int oy);

private:
    int x;
    int y;
    int offsetX;
    int offsetY;

private :
    LatLonWidget * geoWidget;
    coordinateWidget * XYWidget;

signals:
    void coordinateChanged(int X, int Y);
    
public slots:
    void ChangeLatLong(double lat,double lon);
    void ChangeCoordinate(int X, int Y);
    void displayCoordinate(int X, int Y);

};

#endif // LocationWidget_H
