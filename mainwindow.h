#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>

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
    void uniCanalMode();
    void uniCanalMode(QString fichier);
    void multiCanalMode();
    void imageTableView();
};

#endif // MAINWINDOW_H
