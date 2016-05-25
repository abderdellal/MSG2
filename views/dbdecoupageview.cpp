#include "dbdecoupageview.h"


DbDecoupageView::DbDecoupageView(QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout * Hlayout = new QHBoxLayout();
    QVBoxLayout  * Vlayout = new QVBoxLayout();
    myTableView = new QTableView();
    myModel = new QSqlQueryModel(this);

    myTableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    QIcon iconeAfficher("afficher.png");
    QIcon iconeSupprimer("supprimer.png");
    labelBoutton = new QLabel("Pour afficher le decoupage selectionné");
    bouttonAfficher = new QPushButton(iconeAfficher, "Afficher");
    labelSupprimer = new QLabel("Pour supprimer le decoupage selectionné");
    bouttonSupprimer = new QPushButton(iconeSupprimer, "Supprimer");
    bouttonNDVI = new QPushButton("NDVI");

    Hlayout->addWidget(labelBoutton);
    Hlayout->addWidget(bouttonAfficher);
    Hlayout->addWidget(labelSupprimer);
    Hlayout->addWidget(bouttonSupprimer);
    Hlayout->addWidget(bouttonNDVI);
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
    QObject::connect(bouttonNDVI, SIGNAL(clicked()), this, SLOT(NDVI()));
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

void DbDecoupageView::NDVI()
{
    QItemSelectionModel *selection = myTableView->selectionModel();
    QModelIndex indexElementSelectionne = selection->currentIndex();
    int row = indexElementSelectionne.row();
    QModelIndex index = myModel->index(row, 10);
    int ID = myModel->data(index, Qt::DisplayRole).toInt();
    index = myModel->index(row, 1);
    int offsetX = myModel->data(index, Qt::DisplayRole).toInt();
    index = myModel->index(row, 2);
    int offsetY = myModel->data(index, Qt::DisplayRole).toInt();
    /*
    index = myModel->index(row, 3);
    int width = myModel->data(index, Qt::DisplayRole).toInt();
    index = myModel->index(row, 4);
    int height = myModel->data(index, Qt::DisplayRole).toInt();
    */
    QSqlQuery query;
    query.prepare("SELECT chemin FROM images WHERE canal = 'VIS006' and decoupageId = :id");
    query.bindValue(":id", ID);
    bool ok = query.exec();
    if(ok)
    {
        query.next();
        QString chemin1 = query.value(0).toString();
        query.prepare("SELECT chemin FROM images WHERE canal = 'VIS008' and decoupageId = :id");
        query.bindValue(":id", ID);
        bool ok = query.exec();
        if(ok)
        {
            query.next();
            QString chemin2 = query.value(0).toString();
            Image * img06 = new Image(chemin1);
            Image * img08 = new Image(chemin2);
            img06->setOffsetX(offsetX);
            img06->setOffsetY(offsetY);
            img08->setOffsetX(offsetX);
            img08->setOffsetY(offsetY);
            Image * imgNDVI = Calcul::NDVI(img06, img08);
            imgNDVI->setOffsetX(offsetX);
            imgNDVI->setOffsetY(offsetY);
            delete img06;
            delete img08;
            emit imageToDisplay(imgNDVI);
        }
    }
}
