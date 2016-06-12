#ifndef DBDECOUPAGEVIEW_H
#define DBDECOUPAGEVIEW_H

#include <QWidget>
#include <QModelIndex>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSqlQuery>
#include <QTableView>
#include <QLabel>
#include <QPushButton>
#include <QSqlQueryModel>
#include "db.h"
#include "image.h"
#include "calcul.h"

class DbDecoupageView : public QWidget
  {
    Q_OBJECT
public:
    explicit DbDecoupageView(QWidget *parent = 0);

private:
    QSqlQueryModel * myModel;
    QTableView * myTableView;
    QLabel * labelBoutton;
    QPushButton * bouttonAfficher;
    QLabel * labelSupprimer;
    QPushButton * bouttonSupprimer;
    QPushButton * bouttonNDVI;

    
signals:
    void decoupageSelected(QString fichier, QString finF, int offsetX, int OffsetY);
    void imageToDisplay(Image * img);

public slots:
    void clicSelection();
    void supprDecoupage();
    void NDVI();

};

#endif // DBDECOUPAGEVIEW_H
