#include "dbdecoupageview.h"
#include "db.h"

DbDecoupageView::DbDecoupageView(QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout * Hlayout = new QHBoxLayout();
    QVBoxLayout  * Vlayout = new QVBoxLayout();
    myTableView = new QTableView();
    myModel = new QSqlQueryModel(this);

    labelBoutton = new QLabel("Pour afficher le decoupage selectionné");
    bouttonAfficher = new QPushButton("Afficher");
    labelSupprimer = new QLabel("Pour supprimer le decoupage selectionné");
    bouttonSupprimer = new QPushButton("Supprimer");
    Hlayout->addWidget(labelBoutton);
    Hlayout->addWidget(bouttonAfficher);
    Hlayout->addWidget(labelSupprimer);
    Hlayout->addWidget(bouttonSupprimer);
    Hlayout->addStretch();
    Vlayout->addLayout(Hlayout);
    Vlayout->addWidget(myTableView);

    myModel->setQuery("SELECT nom, x, y, width, height, jour, heure, quartDheur, dateCreated, chemin, id FROM decoupages");
    myModel->setHeaderData(0, Qt::Horizontal, "Nom decoupage");
    myModel->setHeaderData(1, Qt::Horizontal, "X");
    myModel->setHeaderData(2, Qt::Horizontal, "Y");
    myModel->setHeaderData(3, Qt::Horizontal, "Width");
    myModel->setHeaderData(4, Qt::Horizontal, "Height");
    myModel->setHeaderData(5, Qt::Horizontal, "Jour");
    myModel->setHeaderData(6, Qt::Horizontal, "Heure");
    myModel->setHeaderData(7, Qt::Horizontal, "Minute");
    myModel->setHeaderData(8, Qt::Horizontal, "Date de Creation");
    myModel->setHeaderData(9, Qt::Horizontal, "Chemin");
    myModel->setHeaderData(10, Qt::Horizontal, "ID");

    myTableView->setColumnHidden(10, true);
    myTableView->setModel(myModel);

    this->setLayout(Vlayout);
    QObject::connect(bouttonAfficher, SIGNAL(clicked()), this, SLOT(clicSelection()));
    QObject::connect(bouttonSupprimer, SIGNAL(clicked()), this, SLOT(supprDecoupage()));
}


void DbDecoupageView::clicSelection()
{
    QItemSelectionModel *selection = myTableView->selectionModel();
    QModelIndex indexElementSelectionne = selection->currentIndex();
    int row = indexElementSelectionne.row();
    QModelIndex index = myModel->index(row, 9);
    QVariant elementSelectionne = myModel->data(index, Qt::DisplayRole);
    QString path = elementSelectionne.toString();
    index = myModel->index(row, 1);
    int offsetX = myModel->data(index, Qt::DisplayRole).toInt();
    index = myModel->index(row, 2);
    int offsetY = myModel->data(index, Qt::DisplayRole).toInt();
    QString finF;
    index = myModel->index(row, 6);
    finF.append(myModel->data(index, Qt::DisplayRole).toString());
    index = myModel->index(row, 7);
    finF.append(myModel->data(index, Qt::DisplayRole).toString());
    emit decoupageSelected(path, finF, offsetX, offsetY);
}

void DbDecoupageView::supprDecoupage()
{
    QItemSelectionModel *selection = myTableView->selectionModel();
    QModelIndex indexElementSelectionne = selection->currentIndex();
    int row = indexElementSelectionne.row();
    QModelIndex index = myModel->index(row, 10);
    QVariant elementSelectionne = myModel->data(index, Qt::DisplayRole);
    int ID = elementSelectionne.toInt();
    index = myModel->index(row, 9);
    QString chemin = myModel->data(index, Qt::DisplayRole).toString();
    DB::supprDecoupage(ID, chemin);

    myModel->removeRow(row);
    myTableView->hideRow(row);

}
