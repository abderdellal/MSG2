#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "multicanaldisplay.h"
#include "unicanaldisplay.h"
#include "dbimagesview.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mode = uni;
    layout = new QVBoxLayout();
    layout->setMargin(0);
    ui->centralWidget->setLayout(layout);
    QObject::connect(ui->actionUni_canal, SIGNAL(triggered()), this, SLOT(uniCanalMode()));
    QObject::connect(ui->actionMulticanal, SIGNAL(triggered()), this, SLOT(multiCanalMode()));
    QObject::connect(ui->actionImages_enregistr_s, SIGNAL(triggered()), this, SLOT(imageTableView()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::imageTableView()
{
    mode = Table;
    clearCentralWidget();
    DbImagesView * imagesView = new DbImagesView();
    layout->addWidget(imagesView);
    QObject::connect(imagesView, SIGNAL(imageSelected(QString)), this, SLOT(uniCanalMode(QString)));
}

void MainWindow::uniCanalMode()
{
    mode = uni;
    clearCentralWidget();
    UniCanalDisplay * uniCanal = new UniCanalDisplay();
    layout->addWidget(uniCanal);
}

void MainWindow::uniCanalMode(QString fichier)
{
    mode = uni;
    clearCentralWidget();
    UniCanalDisplay * uniCanal = new UniCanalDisplay(fichier);
    layout->addWidget(uniCanal);
}

void MainWindow::multiCanalMode()
{
    mode = multi;
    clearCentralWidget();
    MultiCanalDisplay * multicanal = new MultiCanalDisplay();
    layout->addWidget(multicanal);
}

void MainWindow::clearCentralWidget()
{
    QLayoutItem* item;
        while ( ( item = layout->takeAt( 0 ) ) != NULL )
        {
            delete item->widget();
            delete item;
        }
}
