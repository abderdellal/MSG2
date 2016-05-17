#include "latlonwidget.h"
#include <QHBoxLayout>
#include <QMessageBox>

LatLonWidget::LatLonWidget(QWidget *parent) :
    QWidget(parent)
{
    lat = 0;
    lon = 0;

    QHBoxLayout * layout = new QHBoxLayout();
    labelLat = new QLabel("Latitude ");
    editLat = new QLineEdit();
    labelLon = new QLabel("Longitude ");
    editLon = new QLineEdit();
    boutton = new QPushButton("Select");

    editLat->setMaximumWidth(55);
    editLon->setMaximumWidth(55);
    editLat->setMinimumWidth(55);
    editLon->setMinimumWidth(55);

    layout->addWidget(labelLat);
    layout->addWidget(editLat);
    layout->addWidget(labelLon);
    layout->addWidget(editLon);
    layout->addWidget(boutton);

    this->setLayout(layout);

    QObject::connect(boutton, SIGNAL(clicked()), this, SLOT(changeLatLon()));
}


int LatLonWidget::setLat(QString LAT)
{
    bool ok;
    double temp = LAT.toDouble(&ok);
    if(ok)
    {
       lat = temp;
       return 0;
    }
    else
    {
        QMessageBox::question(this, "Erreur","Vérifier le Champ Latitude");
        return 1;
    }
}

int LatLonWidget::setLon(QString LON)
{
    bool ok;
    double temp = LON.toDouble(&ok);
    if(ok)
    {
       lon = temp;
       return 0;
    }
    else
    {
        QMessageBox::question(this, "Erreur","Vérifier le Champ Longitude");
        return 1;
    }
}

void LatLonWidget::setLatLon(double LAT, double LON)
{
    QString s;

    lat = LAT;
    s.setNum(lat);
    editLat->setText(s);

    lon = LON;
    s.setNum(lon);
    editLon->setText(s);
}

int LatLonWidget::getLat()
{
    return lat;
}

int LatLonWidget::getLon()
{
    return lon;
}

void LatLonWidget::changeLatLon()
{
    int b = 0;

    QString s;
    s = editLat->text();
    b = b + setLat(s);

    s = editLon->text();
    b = b + setLon(s);

    if(b == 0)
    {
        emit latLonChanged(lat, lon);
    }
}
