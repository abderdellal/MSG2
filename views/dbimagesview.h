#ifndef DBIMAGESVIEW_H
#define DBIMAGESVIEW_H

#include "db.h"
#include "image.h"

#include <QWidget>
#include <QSqlQueryModel>
#include <QTableView>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>

class DbImagesView : public QWidget
{
    Q_OBJECT
public:
    explicit DbImagesView(QWidget *parent = 0);

private:
    QSqlQueryModel * myModel;
    QTableView * myTableView;
    QLabel * labelBoutton;
    QPushButton * bouttonAfficher;
    QPushButton * bouttonSupprimer;
    QPushButton * bouttonDifference;
    QPushButton * bouttonCorrelaion;
    
signals:
    void imageSelected(QString fichier, int offsetX, int OffsetY);
    void imageSelected(Image * img);
public slots:
    void clicSelection();
    void supprImage();
    void difference();
    void correlation();
};

#endif // DBIMAGESVIEW_H
