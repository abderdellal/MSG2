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
    
signals:
    void decoupageSelected(QString fichier, QString finF, int offsetX, int OffsetY);

public slots:
    void clicSelection();
    void supprDecoupage();

};

#endif // DBDECOUPAGEVIEW_H
