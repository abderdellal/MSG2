#ifndef SELECTDAYENNUAGEMENT_H
#define SELECTDAYENNUAGEMENT_H

#include <QWidget>
#include "selectday.h"
#include "multicanalcontroller.h"
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>
#include <QComboBox>
#include <QSqlQuery>
#include <QFileDialog>
#include <QDirIterator>

class SelectDayEnnuagement : public QWidget
{
    Q_OBJECT
public:
    explicit SelectDayEnnuagement(QWidget *parent = 0);


private:
    QString dossier;

    QLabel * labelDossier;
    QPushButton * bouttonDossier;
    QLabel * labelDate1;
    SelectDay * selectday1;
    QLabel * labelDate2;
    SelectDay * selectday2;
    QLabel * decoupageLabel;
    QComboBox * decoupageBox;
    QLabel * labelHeur;
    QComboBox * comboHeur;
    QLabel * labelMinute;
    QComboBox * comboMinute;
    QPushButton * bouttonCalcul;

    QList<QString> decoupagesList;
    QList<QString> decoupagesNameList;

    void populateComboDecoupage();
    void populateComboHeure();
    void populateComboMinute();

signals:
    void intervalSelected(QList<QString> folderList, QString finF);

public slots:
    void getFolders();
    void selectDossier();

    
};

#endif // SELECTDAYENNUAGEMENT_H
