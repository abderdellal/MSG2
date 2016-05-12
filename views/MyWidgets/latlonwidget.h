#ifndef LatLonWidget_H
#define LatLonWidget_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>


class LatLonWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LatLonWidget(QWidget *parent = 0);
    int getLat();
    int getLon();
    int setLat(QString LAT);
    int setLon(QString LON);

private:
    double lat;
    double lon;

    QLabel * labelLat;
    QLineEdit * editLat;
    QLabel * labelLon;
    QLineEdit * editLon;
    QPushButton * boutton;
    
signals:
    void latLonChanged(double LAT, double LON);
    
public slots:
    void setLatLon(double LAT, double LON);
    void changeLatLon();
};

#endif // LatLonWidget_H
