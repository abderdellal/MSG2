#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "multicanaldisplay.h"
#include "unicanaldisplay.h"
#include "dbimagesview.h"
#include "dbdecoupageview.h"

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
    QObject::connect(ui->actionDecoupage_enregistr_s, SIGNAL(triggered()), this, SLOT(decoupageTableView()));
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
    QObject::connect(imagesView, SIGNAL(imageSelected(QString,int,int)), this, SLOT(uniCanalMode(QString,int,int)));
}

void MainWindow::decoupageTableView()
{
    mode = Table;
    clearCentralWidget();
    DbDecoupageView * decoupageView = new DbDecoupageView();
    layout->addWidget(decoupageView);
    QObject::connect(decoupageView, SIGNAL(decoupageSelected(QString,QString,int,int)), this, SLOT(multiCanalMode(QString,QString,int,int)));
}

void MainWindow::uniCanalMode()
{
    mode = uni;
    clearCentralWidget();
    UniCanalDisplay * uniCanal = new UniCanalDisplay();
    layout->addWidget(uniCanal);
}

void MainWindow::uniCanalMode(QString fichier, int offsetX, int offsetY)
{
    mode = uni;
    clearCentralWidget();
    UniCanalDisplay * uniCanal = new UniCanalDisplay(fichier, offsetX, offsetY);
    layout->addWidget(uniCanal);
}

void MainWindow::multiCanalMode()
{
    mode = multi;
    clearCentralWidget();
    MultiCanalDisplay * multicanal = new MultiCanalDisplay();
    layout->addWidget(multicanal);
}

void MainWindow::multiCanalMode(QString dossier, QString finF,int offsetX, int offsetY)
{
    mode = multi;
    clearCentralWidget();
    MultiCanalDisplay * multicanal = new MultiCanalDisplay();
    multicanal->setOffsetX(offsetX);
    multicanal->setOffsetY(offsetY);
    multicanal->setDossier(dossier);
    multicanal->setFinF(finF);
    layout->addWidget(multicanal);
    multicanal->afficherImage();
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
