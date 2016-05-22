#include "dbimagesview.h"
#include "QDebug"

DbImagesView::DbImagesView(QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout * Hlayout = new QHBoxLayout();
    QVBoxLayout  * Vlayout = new QVBoxLayout();
    myTableView = new QTableView();
    myModel = new QSqlQueryModel(this);

    labelBoutton = new QLabel("Pour afficher l'image selectionnée");
    bouttonAfficher = new QPushButton("Afficher");
    bouttonSupprimer = new QPushButton("Supprimer");
    Hlayout->addWidget(labelBoutton);
    Hlayout->addWidget(bouttonAfficher);
    Hlayout->addWidget(bouttonSupprimer);
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
