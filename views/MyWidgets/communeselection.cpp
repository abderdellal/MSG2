#include "communeselection.h"
#include "QHBoxLayout"

CommuneSelection::CommuneSelection(QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout * layout = new QHBoxLayout();
    labelWilaya = new QLabel("Wilaya");
    comboWilaya = new QComboBox();
    labelCommune = new QLabel("Commune");
    comboCommune = new QComboBox();
    bouttonSelect = new QPushButton("Select");
    layout->addWidget(labelWilaya);
    layout->addWidget(comboWilaya);
    layout->addWidget(labelCommune);
    layout->addWidget(comboCommune);
    layout->addWidget(bouttonSelect);
    populateWilaya();
    this->setLayout(layout);
    QObject::connect(comboWilaya, SIGNAL(currentIndexChanged(QString)), this, SLOT(populateComuune(QString)));
    QObject::connect(bouttonSelect, SIGNAL(clicked()), this, SLOT(SelectCommune()));
}

void CommuneSelection::populateWilaya()
{
    if(comboWilaya)
    comboWilaya->clear();
    QStringList list;
    list = DB::getWilayas();
    foreach(QString wilaya, list)
    {
        comboWilaya->addItem(wilaya);
    }
}

void CommuneSelection::populateComuune(QString wilaya)
{
    if(comboCommune)
    comboCommune->clear();
    QStringList list;
    list = DB::getCommunes(wilaya);
    foreach(QString commune, list)
    {
        comboCommune->addItem(commune);
    }
}

void CommuneSelection::SelectCommune()
{
    QString wilaya = comboWilaya->currentText();
    QString commune = comboCommune->currentText();
    double lat;
    double lon;
    DB::getLatLon(commune, wilaya, lat, lon);
    emit communeSelected(lat, lon);
}
