#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "image.h"
#include "ennuagementview.h"

enum Mode{uni, multi, Table};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    void clearCentralWidget();
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    QVBoxLayout * layout;
    Mode mode;


signals:

public slots:
    void RVBMode();
    void uniCanalMode();
    void uniCanalMode(QString fichier, int offsetX, int offsetY);
    void uniCanalMode(Image * img);
    void multiCanalMode();
    void multiCanalMode(QString fichier, QString finF, int offsetX, int offsetY);
    void imageTableView();
    void decoupageTableView();
    void correlationTemp();
    void ennuagement();
};

#endif // MAINWINDOW_H
