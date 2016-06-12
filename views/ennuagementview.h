#ifndef ENNUAGEMENTVIEW_H
#define ENNUAGEMENTVIEW_H

#include <QWidget>
#include "selectdayennuagement.h"
#include "imagecontroller.h"

class EnnuagementView : public QWidget
{
    Q_OBJECT
public:
    explicit EnnuagementView(QWidget *parent = 0);

private:
    SelectDayEnnuagement * selectDays;
    
signals:
    
public slots:
    void calculerEnnuagement(QList<QString> folderList, QString finF);

};

#endif // ENNUAGEMENTVIEW_H
