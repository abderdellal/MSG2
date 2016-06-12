#include "selectdayennuagement.h"

SelectDayEnnuagement::SelectDayEnnuagement(QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout * Vlayout = new QVBoxLayout();
    QHBoxLayout * layoutHeure  = new QHBoxLayout();
    QHBoxLayout * layoutDossier  = new QHBoxLayout();
    QHBoxLayout * layoutDecoupages  = new QHBoxLayout();

    labelDate1 = new QLabel("Date 1");
    selectday1 = new SelectDay();
    labelDate2 = new QLabel("Date 2");
    selectday2 = new SelectDay();

    labelHeur = new QLabel("Heure ");
    comboHeur = new QComboBox();
    populateComboHeure();
    labelMinute = new QLabel("Quart d'heure ");
    comboMinute = new QComboBox();
    populateComboMinute();


    labelDossier = new QLabel("Dossier d'images");
    bouttonDossier = new QPushButton("Ouvrir");
    bouttonDossier->setMaximumWidth(150);

    decoupageLabel = new QLabel("Decoupages ");
    decoupageBox = new QComboBox();
    populateComboDecoupage();

    bouttonCalcul = new QPushButton("Calculer la correlation");
    bouttonCalcul->setMaximumWidth(180);

    Vlayout->addWidget(labelDate1);
    Vlayout->addWidget(selectday1);
    Vlayout->addWidget(labelDate2);
    Vlayout->addWidget(selectday2);

    layoutHeure->addWidget(labelHeur);
    layoutHeure->addWidget(comboHeur);
    layoutHeure->addWidget(labelMinute);
    layoutHeure->addWidget(comboMinute);

    Vlayout->addLayout(layoutHeure);

    Vlayout->addSpacing(30);

    layoutDossier->addWidget(labelDossier);
    layoutDossier->addWidget(bouttonDossier);

    Vlayout->addLayout(layoutDossier);

    layoutDecoupages->addWidget(decoupageLabel);
    layoutDecoupages->addWidget(decoupageBox);

    Vlayout->addLayout(layoutDecoupages);
    Vlayout->addSpacing(10);

    Vlayout->addWidget(bouttonCalcul);
    Vlayout->setAlignment(bouttonCalcul, Qt::AlignCenter);


    this->setLayout(Vlayout);

    QObject::connect(bouttonDossier, SIGNAL(clicked()), this, SLOT(selectDossier()));
    QObject::connect(bouttonCalcul, SIGNAL(clicked()), this, SLOT(getFolders()));
}



void SelectDayEnnuagement::getFolders()
{
    QList<QString> foldersList;
    bool valide = false;

    valide = (selectday1->check() && selectday2->check());

    if(valide)
    {
        QString date1 = selectday1->getDate();
        QString date2 = selectday2->getDate();

        if(date2 > date1)
        {
            QString heure = comboHeur->itemText(comboHeur->currentIndex());
            QString minute = comboMinute->itemText(comboMinute->currentIndex());
            QString finF;
            finF.append(heure);
            finF.append(minute);

            if(dossier.size() > 0)
            {
                QDirIterator it(dossier);

                do
                {
                    it.next();
                    QString cheminDossier = it.filePath();
                    QString nomDossier = it.fileName();
                    QFileInfo info(cheminDossier);
                    if (info.isDir() && nomDossier >= date1 && nomDossier <= date2)
                    {
                        foldersList.append(cheminDossier);
                    }
                }while(it.hasNext());

            }
            else
            {
                QString decoupage = decoupagesList.at(decoupageBox->currentIndex() - 1);

                dossier = ".\\decoupages";
                QDirIterator it(dossier);
                do
                {
                    it.next();
                    QString cheminDossier = it.filePath();
                    QString nomDossier = it.fileName();
                    QFileInfo info(cheminDossier);
                    if (info.isDir() && nomDossier >= date1 && nomDossier <= date2)
                    {
                        QString s;
                        s.append(cheminDossier);
                        s.append("/");
                        s.append(decoupage);
                        QDir dir(s);
                        if (dir.exists())
                        {
                            foldersList.append(s);
                        }
                    }
                }while(it.hasNext());


            }

            emit intervalSelected(foldersList, finF);
        }
        else
        {
            QMessageBox::question(this, "Erreur", "la première date est supérieure à la deuxième");
        }
    }
    else
    {
        QMessageBox::question(this, "Erreur", "Vérifiez les dates entrées");
    }

}


void SelectDayEnnuagement::populateComboDecoupage()
{

    QSqlQuery query("SELECT DISTINCT nom, x, y, width, height FROM decoupages");
    while (query.next())
    {
        QString s;
        QString s2;
        s2.append(query.value(0).toString());

        s.append("decoupage(");
        s.append(query.value(1).toString());
        s.append("-");
        s.append(query.value(2).toString());
        s.append("-");
        s.append(query.value(3).toString());
        s.append("-");
        s.append(query.value(4).toString());
        s.append(")");


       decoupagesList.append(s);
       decoupagesNameList.append(s2);
    }

    decoupageBox->addItem(QString());
    int i = 0;
    foreach(QString decoupage, decoupagesList)
    {
        QString s = decoupagesNameList.at(i);
        s.append(" - ");
        s.append(decoupage);
        decoupageBox->addItem(s);
    }
}


void SelectDayEnnuagement::populateComboHeure()
{
    comboHeur->addItem("05");
    comboHeur->addItem("06");
    comboHeur->addItem("07");
    comboHeur->addItem("08");
    comboHeur->addItem("09");
    comboHeur->addItem("10");
    comboHeur->addItem("11");
    comboHeur->addItem("12");
    comboHeur->addItem("13");
    comboHeur->addItem("14");
    comboHeur->addItem("15");
    comboHeur->addItem("16");
    comboHeur->addItem("17");
    comboHeur->addItem("19");
    comboHeur->addItem("20");
    comboHeur->addItem("21");
    comboHeur->addItem("22");
    comboHeur->addItem("23");
}

void SelectDayEnnuagement::populateComboMinute()
{
    comboMinute->addItem("30");
    comboMinute->addItem("45");
    comboMinute->addItem("00");
    comboMinute->addItem("15");
}

void SelectDayEnnuagement::selectDossier()
{
    dossier = QFileDialog::getExistingDirectory(this, "Dossier PGM", ".\\base_images");
    if(dossier.size() > 0)
    {
        labelDossier->setText(dossier.section('\\', -1));
    }
}
