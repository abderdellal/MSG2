#include "imagesselectwidget.h"
#include <QHBoxLayout>
#include <QFileDialog>
#include <QMessageBox>

ImagesSelectWidget::ImagesSelectWidget(QWidget *parent) :
    QWidget(parent)
{
    dossier = "";
    heure = "05";
    minute = "30";

    QHBoxLayout * layout = new QHBoxLayout();
    labelDossier = new QLabel("Cliquez pour choisir un dossier d'image");
    bouttonDossier = new QPushButton("Dossier");
    QIcon icone;
    icone.addFile(QString::fromUtf8("dossier.png"), QSize(), QIcon::Normal, QIcon::Off);
    bouttonDossier->setIcon(icone);
    labelHeure = new QLabel("Spécifier l'heure" );
    comboHeure = new QComboBox();
    comboHeure->addItem("05");
    comboHeure->addItem("06");
    comboHeure->addItem("07");
    comboHeure->addItem("08");
    comboHeure->addItem("09");
    comboHeure->addItem("10");
    comboHeure->addItem("11");
    comboHeure->addItem("12");
    comboHeure->addItem("13");
    comboHeure->addItem("14");
    comboHeure->addItem("15");
    comboHeure->addItem("16");
    comboHeure->addItem("17");
    comboHeure->addItem("19");
    comboHeure->addItem("20");
    comboHeure->addItem("21");
    comboHeure->addItem("22");
    comboHeure->addItem("23");
    labelMinute = new QLabel("Spécifier la minute");
    comboMinute = new QComboBox();
    comboMinute->addItem("30");
    comboMinute->addItem("45");
    comboMinute->addItem("00");
    comboMinute->addItem("15");
    bouttonSelect = new QPushButton("Charger Images");

    layout->addWidget(labelDossier);
    layout->addWidget(bouttonDossier);
    layout->addWidget(labelHeure);
    layout->addWidget(comboHeure);
    layout->addWidget(labelMinute);
    layout->addWidget(comboMinute);
    layout->addWidget(bouttonSelect);

    this->setLayout(layout);

    QObject::connect(bouttonDossier, SIGNAL(clicked()), this, SLOT(bouttonDossierClicked()));
    QObject::connect(bouttonSelect, SIGNAL(clicked()), this, SLOT(bouttonSelectClicked()));
    QObject::connect(comboHeure,SIGNAL(currentIndexChanged(QString)), this, SLOT(setHeure(QString)));
    QObject::connect(comboMinute,SIGNAL(currentIndexChanged(QString)), this, SLOT(setMinute(QString)));

}

void ImagesSelectWidget::setHeure(QString h)
{
    heure = h;
}

void ImagesSelectWidget::setMinute(QString m)
{
    minute = m;
}

void ImagesSelectWidget::bouttonDossierClicked()
{
    dossier = QFileDialog::getExistingDirectory(this, "Dossier PGM", ".\\base_images");
    labelDossier->setText(dossier.section('\\', -1));
}

void ImagesSelectWidget::bouttonSelectClicked()
{
    if(heure == "")
    {
        QMessageBox::question(this, "Time not Specefied", "Vous devez spécifier une heure dans la journée");
    }
    else if(minute == "")
    {
        QMessageBox::question(this, "Time not Specefied", "Vous devez spécifier le quart d'heure");
    }
    else if(dossier == "")
    {
        QMessageBox::question(this, "Time not Specified", "Vous devez spécifier le dossier d'images");
    }
    else{
        QString fin = heure;
        fin.append(minute);
        emit folderSelected(dossier, fin);
    }

}
