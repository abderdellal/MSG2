#ifndef COMMUNESELECTION_H
#define COMMUNESELECTION_H

#include "db.h"
#include <QWidget>
#include <QString>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>

class CommuneSelection : public QWidget
{
    Q_OBJECT
public:
    explicit CommuneSelection(QWidget *parent = 0);
    void populateWilaya();

private:
    QLabel * labelWilaya;
    QComboBox * comboWilaya;
    QLabel * labelCommune;
    QComboBox * comboCommune;
    QPushButton * bouttonSelect;

signals:
    void communeSelected(double lat, double lon);
    
public slots:
    void populateComuune(QString wilaya);
    void SelectCommune();

};

#endif // COMMUNESELECTION_H
