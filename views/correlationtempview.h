#ifndef CORRELATIONTEMPVIEW_H
#define CORRELATIONTEMPVIEW_H

#include <QWidget>
#include <QGridLayout>
#include "selectdayinterval.h"
#include "imagecontroller.h"

class CorrelationTempView : public QWidget
{
    Q_OBJECT
public:
    explicit CorrelationTempView(QWidget *parent = 0);

private:
    SelectDayInterval * selectInterval;
    
signals:
    
public slots:
    void calculerCorrelation(QList<QString> folderList, QString finF, QString canal);
    
};

#endif // CORRELATIONTEMPVIEW_H
