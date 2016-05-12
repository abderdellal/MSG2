#ifndef IMAGESSELECTWIDGET_H
#define IMAGESSELECTWIDGET_H

#include <QWidget>
#include <QString>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>

class ImagesSelectWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ImagesSelectWidget(QWidget *parent = 0);

private:
    QString dossier;
    QString heure;
    QString minute;

    QLabel * labelDossier;
    QPushButton * bouttonDossier;
    QLabel * labelHeure;
    QComboBox * comboHeure;
    QLabel * labelMinute;
    QComboBox * comboMinute;
    QPushButton * bouttonSelect;

signals:
    void folderSelected(QString, QString finfichier);
public slots:
    void bouttonDossierClicked();
    void bouttonSelectClicked();
    void setHeure(QString);
    void setMinute(QString);
};

#endif // IMAGESSELECTWIDGET_H
