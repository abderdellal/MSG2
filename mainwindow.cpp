#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "multicanaldisplay.h"
#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGridLayout * layout = new QGridLayout();
    MultiCanalDisplay * multicanal = new MultiCanalDisplay();
    layout->addWidget(multicanal, 0, 0);
    centralWidget()->setLayout(layout);
}

MainWindow::~MainWindow()
{
    delete ui;
}
