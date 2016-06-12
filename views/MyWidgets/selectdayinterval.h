#ifndef SELECTDAYINTERVAL_H
#define SELECTDAYINTERVAL_H

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

class SelectDayInterval : public QWidget
{
    Q_OBJECT
public:
    explicit SelectDayInterval(QWidget *parent = 0);
    
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


    QLabel * labelCanal;
    QComboBox * comboCanal;


    QList<QString> decoupagesList;
    QList<QString> decoupagesNameList;

    void populateComboDecoupage();
    void populateComboCanal();
    void populateComboHeure();
    void populateComboMinute();

signals:
    void intervalSelected(QList<QString> folderList, QString finF, QString canal);

public slots:
    void getFolders();
    void selectDossier();
    
};

#endif // SELECTDAYINTERVAL_H
