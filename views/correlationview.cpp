#include "correlationview.h"

CorrelationView::CorrelationView(std::map<QString, Image*> imagesMap, QWidget *parent) :
    QWidget(parent)
{
    QGridLayout * Glayout = new QGridLayout();
    QVBoxLayout * Vlayout = new QVBoxLayout();
    QHBoxLayout * Hlayout = new QHBoxLayout();
    QPushButton * bouttonFermer = new QPushButton("Fermer");
    Hlayout->addWidget(bouttonFermer);
    Hlayout->setAlignment(bouttonFermer, Qt::AlignCenter);
    Vlayout->addLayout(Glayout);
    Vlayout->addLayout(Hlayout);

    std::map<QString, Image *>::iterator it;
    int i = 1;
    for(it = imagesMap.begin() ; it != imagesMap.end() ; ++it)
    {
        QString canal = it->first;

        QLabel * labelCanal = new QLabel(canal);
        labelCanal->setMargin(10);
        Glayout->addWidget(labelCanal, 0, i);
        i++;
    }

    i = 1;
    for(it = imagesMap.begin() ; it != imagesMap.end() ; ++it)
    {
        QString canal = it->first;
        Image * img = it->second;

        QLabel * labelCanal = new QLabel(canal);
        labelCanal->setMargin(10);
        Glayout->addWidget(labelCanal, i, 0);

        int j = 1;
        std::map<QString, Image *>::iterator it2;
        for(it2 = imagesMap.begin() ; it2 != imagesMap.end() ; ++it2)
        {
            Image * img2 = it2->second;

            double correlation = img->correlation(img2);
            QString stringCorr = (new QString())->number(correlation);

            QLabel * labelCorr = new QLabel(stringCorr);
            labelCorr->setMargin(10);
            Glayout->addWidget(labelCorr, i, j);

            j++;
        }
        i++;
    }

    this->setLayout(Vlayout);
    QObject::connect(bouttonFermer, SIGNAL(clicked()), this, SLOT(close()));
}
