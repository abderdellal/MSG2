#ifndef SELECTDAY_H
#define SELECTDAY_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>

class SelectDay : public QWidget
{
    Q_OBJECT
public:
    explicit SelectDay(QWidget *parent = 0);
    QString getDate();
    bool check();

private:
    QLabel * labelAnnee;
    QLineEdit * editAnnee;
    QLabel * labelMois;
    QLineEdit * editMois;
    QLabel * labelJour;
    QLineEdit * editJour;
    
signals:
    
public slots:
    
};

#endif // SELECTDAY_H
