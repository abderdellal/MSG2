#include "dbimagesview.h"
#include "QDebug"
#include "image.h"

DbImagesView::DbImagesView(QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout * Hlayout = new QHBoxLayout();
    QVBoxLayout  * Vlayout = new QVBoxLayout();
    myTableView = new QTableView();
    myModel = new QSqlQueryModel(this);

    myTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    myTableView->setSelectionMode(QAbstractItemView::ExtendedSelection);

    labelBoutton = new QLabel("Pour afficher l'image selectionnée");
    QIcon iconeAfficher("afficher.png");
    QIcon iconeSupprimer("supprimer.png");
    QIcon iconeDifference("difference.png");
    bouttonAfficher = new QPushButton(iconeAfficher, "Afficher");
    bouttonSupprimer = new QPushButton(iconeSupprimer, "Supprimer");
    bouttonDifference = new QPushButton(iconeDifference, "Difference");
    Hlayout->addWidget(labelBoutton);
    Hlayout->addWidget(bouttonAfficher);
    Hlayout->addWidget(bouttonSupprimer);
    Hlayout->addWidget(bouttonDifference);
    Hlayout->addStretch();
    Vlayout->addLayout(Hlayout);
    Vlayout->addWidget(myTableView);

    myModel->setQuery("SELECT canal, img.chemin, nom, x, y, width, height, jour, heure, quartDheur, dateCreated, img.id  FROM decoupages dec, images img WHERE dec.id = img.decoupageID");
    myModel->setHeaderData(0, Qt::Horizontal, "Canal");
    myModel->setHeaderData(1, Qt::Horizontal, "Chemin");
    myModel->setHeaderData(2, Qt::Horizontal, "Nom decoupage");
    myModel->setHeaderData(3, Qt::Horizontal, "X");
    myModel->setHeaderData(4, Qt::Horizontal, "Y");
    myModel->setHeaderData(5, Qt::Horizontal, "Width");
    myModel->setHeaderData(6, Qt::Horizontal, "Height");
    myModel->setHeaderData(7, Qt::Horizontal, "Jour");
    myModel->setHeaderData(8, Qt::Horizontal, "Heure");
    myModel->setHeaderData(9, Qt::Horizontal, "Minute");
    myModel->setHeaderData(10, Qt::Horizontal, "Date de Creation");
    myModel->setHeaderData(11, Qt::Horizontal, "ID Image");

    myTableView->setModel(myModel);
    myTableView->setColumnHidden(11, true);

    this->setLayout(Vlayout);
    QObject::connect(bouttonAfficher, SIGNAL(clicked()), this, SLOT(clicSelection()));
    QObject::connect(bouttonSupprimer, SIGNAL(clicked()), this, SLOT(supprImage()));
    QObject::connect(bouttonDifference, SIGNAL(clicked()), this, SLOT(difference()));
}


void DbImagesView::clicSelection()
{
    QItemSelectionModel *selection = myTableView->selectionModel();
    QModelIndex indexElementSelectionne = selection->currentIndex();
    int row = indexElementSelectionne.row();
    QModelIndex index = myModel->index(row, 1);
    QVariant elementSelectionne = myModel->data(index, Qt::DisplayRole);
    QString path = elementSelectionne.toString();
    index = myModel->index(row, 3);
    int offsetX = myModel->data(index, Qt::DisplayRole).toInt();
    index = myModel->index(row, 4);
    int offsetY = myModel->data(index, Qt::DisplayRole).toInt();
    emit imageSelected(path, offsetX, offsetY);
}

void DbImagesView::supprImage()
{
    QItemSelectionModel *selection = myTableView->selectionModel();
    QModelIndex indexElementSelectionne = selection->currentIndex();
    int row = indexElementSelectionne.row();
    QModelIndex index = myModel->index(row, 11);
    QVariant elementSelectionne = myModel->data(index, Qt::DisplayRole);
    int ID = elementSelectionne.toInt();
    index = myModel->index(row, 1);
    QString chemin = myModel->data(index, Qt::DisplayRole).toString();
    bool ok = DB::supprImage(ID, chemin);
    ok =ok;
    myModel->removeRow(row);
    myTableView->hideRow(row);
}

void DbImagesView::difference()
{
    QItemSelectionModel *selection = myTableView->selectionModel();
    QModelIndexList listeSelections = selection->selectedRows();

    Image * img1, * img2, * diff;
    QString chemin1, chemin2;
    int width1, width2, height1, height2, offsetx1, offsetx2, offsety1, offsety2;

    if (listeSelections.size() != 2)
    {
        QMessageBox::question(this, "Erreur", "vous devez selectionner deux images");
    }
    else
    {
        int row = listeSelections.at(0).row();
        QModelIndex index = myModel->index(row, 1);
        chemin1 = myModel->data(index, Qt::DisplayRole).toString();
        index = myModel->index(row, 3);
        offsetx1 = myModel->data(index, Qt::DisplayRole).toInt();
        index = myModel->index(row, 4);
        offsety1 = myModel->data(index, Qt::DisplayRole).toInt();
        index = myModel->index(row, 5);
        width1 = myModel->data(index, Qt::DisplayRole).toInt();
        index = myModel->index(row, 6);
        height1 = myModel->data(index, Qt::DisplayRole).toInt();

        row = listeSelections.at(1).row();
        index = myModel->index(row, 1);
        chemin2 = myModel->data(index, Qt::DisplayRole).toString();
        index = myModel->index(row, 3);
        offsetx2 = myModel->data(index, Qt::DisplayRole).toInt();
        index = myModel->index(row, 4);
        offsety2 = myModel->data(index, Qt::DisplayRole).toInt();
        index = myModel->index(row, 5);
        width2 = myModel->data(index, Qt::DisplayRole).toInt();
        index = myModel->index(row, 6);
        height2 = myModel->data(index, Qt::DisplayRole).toInt();

        if(width1 == width2 && height1 == height2 && offsetx1 == offsetx2 && offsety1 == offsety2)
        {
            img1 = new Image(chemin1);
            img2 = new Image(chemin2);
            diff = img1->difference(img2);
            delete img1;
            delete img2;
            emit imageSelected(diff);
        }
        else
        {
            QMessageBox::question(this, "Erreur", "impossible de faire la difference entre ces deux images");
        }

    }
}
