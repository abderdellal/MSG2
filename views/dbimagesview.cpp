#include "dbimagesview.h"

DbImagesView::DbImagesView(QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout * Hlayout = new QHBoxLayout();
    QVBoxLayout  * Vlayout = new QVBoxLayout();
    myTableView = new QTableView();
    myModel = new QSqlQueryModel(this);

    labelBoutton = new QLabel("Pour afficher l'image selectionnées");
    bouttonAfficher = new QPushButton("Afficher");
    Hlayout->addWidget(labelBoutton);
    Hlayout->addWidget(bouttonAfficher);
    Hlayout->addStretch();
    Vlayout->addLayout(Hlayout);
    Vlayout->addWidget(myTableView);

    myModel->setQuery("SELECT canal, chemin, nom, x, y, width, height, jour, heure, quartDheur, dateCreated, img.id  FROM decoupages dec, images img WHERE dec.id = img.decoupageID");
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
    connect(bouttonAfficher, SIGNAL(clicked()), this, SLOT(clicSelection()));
}


void DbImagesView::clicSelection()
{
    QItemSelectionModel *selection = myTableView->selectionModel();
    QModelIndex indexElementSelectionne = selection->currentIndex();
    int row = indexElementSelectionne.row();
    QModelIndex indexID = myModel->index(row, 1);
    QVariant elementSelectionne = myModel->data(indexID, Qt::DisplayRole);
    QString path = elementSelectionne.toString();
    emit imageSelected(path);
}
