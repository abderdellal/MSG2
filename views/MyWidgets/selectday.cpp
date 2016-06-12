#include "selectday.h"

SelectDay::SelectDay(QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout * Hlayout = new QHBoxLayout();

    labelAnnee = new QLabel("Année ");
    editAnnee = new QLineEdit();
    editAnnee->setMaximumWidth(70);
    labelMois = new QLabel("Mois ");
    editMois = new QLineEdit();
    editMois->setMaximumWidth(70);
    labelJour = new QLabel("Jour ");
    editJour = new QLineEdit();
    editJour->setMaximumWidth(70);

    Hlayout->addWidget(labelAnnee);
    Hlayout->addWidget(editAnnee);
    Hlayout->addWidget(labelMois);
    Hlayout->addWidget(editMois);
    Hlayout->addWidget(labelJour);
    Hlayout->addWidget(editJour);

    this->setLayout(Hlayout);
}

QString SelectDay::getDate()
{
    QString date;
    QString s = editAnnee->text();
    date.append(s);
    s = editMois->text();
    date.append(s);
    s = editJour->text();
    date.append(s);

    return date;
}


bool SelectDay::check()
{
    bool b = true;
    int val = 0;

    QString s;
    s = editAnnee->text();
    val = s.toInt(&b);
    if(s.length() != 4 || val < 1970 || val > 2020)
    {
        b = false;
    }

    s = editMois->text();
    val =  s.toInt(&b);

    if(s.length() != 2 || val < 1 || val > 12)
    {
        b = false;
    }

    s = editJour->text();
    val =  s.toInt(&b);
    if(s.length() != 2 || val < 1 || val > 31)
    {
        b = false;
    }

    return b;
}
