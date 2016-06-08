#include "chartview.h"

ChartView::ChartView(Image * img, QWidget *parent) :
    QWidget(parent)
{
    this->img = img;
    unsigned short * im = img->getData();
    int height = img->getHeight();
    int width = img->getWidth();

    int maxRepet = 0;
    int maxCouleur = 0;
    int minCouleur = 1023;
    long int somme = 0;

    for(int i = 0; i < 1024 ; i++)
    {
        repets.append(0);
    }
    for(int i = 0; i < 1024 ; i++)
    {
        valeurs.append(i);
    }
    for(int i = 0; i < width*height ; i++)
    {
        int indice = im[i]%1024;
        repets[indice] = repets[indice] + 1;
        if(maxCouleur < im[i])
        {
            maxCouleur = im[i];
        }
        if(minCouleur > im[i])
        {
            minCouleur = im[i];
        }
        somme = somme + im[i];
    }

    double moy = (double) somme / (width*height);

    double variance = 0;

    double sommeVar;
    for(int i = 0; i < width*height ; i++)
    {
        double diff = im[i] - moy;
        double diffSquare = pow(diff, 2);
        sommeVar = sommeVar + diffSquare;
    }

    variance = sommeVar / (width*height);

    double equartType = sqrt(variance);

    for(int i = 0; i < repets.size() ; i++)
    {
        if(maxRepet < repets[i])
        {
            maxRepet = repets[i];
        }
    }

    customPlot = new QCustomPlot();



    QCPBars *vals = new QCPBars(customPlot->xAxis, customPlot->yAxis);

    customPlot->xAxis->setAutoTicks(false);
    QVector<double> ticks;
    ticks << 100 <<200 <<300 <<400 <<500 <<600 <<700 <<800 <<900 <<1000;
    customPlot->xAxis->setTickVector(ticks);
    customPlot->xAxis->setRange(0, 1024);
    customPlot->xAxis->setTickStep(100);
    customPlot->yAxis->setRange(0, maxRepet + 2000);

    customPlot->yAxis->setLabel("Répétitions des couleurs");
    customPlot->xAxis->setLabel("couleurs");


    customPlot->addPlottable(vals);
    vals->setName("repetition");

    vals->setData(valeurs, repets);

    customPlot->legend->setVisible(true);
    customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    customPlot->legend->setBrush(QColor(255, 255, 255, 200));
    QPen legendPen;
    legendPen.setColor(QColor(130, 130, 130, 200));
    customPlot->legend->setBorderPen(legendPen);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    customPlot->legend->setFont(legendFont);
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    customPlot->yAxis->grid()->setSubGridVisible(true);
    customPlot->xAxis->grid()->setSubGridVisible(true);








    QGridLayout * Glayout= new QGridLayout();
    QHBoxLayout * Hlayout = new QHBoxLayout();

    labelMaxCouleur = new QLabel("Couleur Max ");
    labelMinCouleur = new QLabel("Couleur Min");
    labelMoyenne = new QLabel("Moyenne");
    labelVariance = new QLabel("Variance");
    labelEquarType = new QLabel("Equart type");

    editMaxCouleur = new QLineEdit(QString().number(maxCouleur));
    editMinCouleur = new QLineEdit(QString().number(minCouleur));
    editMoyenne = new QLineEdit(QString().number(moy));
    editVariance = new QLineEdit(QString().number(variance));
    editEquarType = new QLineEdit(QString().number(equartType));

    editMaxCouleur->setMaximumWidth(100);
    editMinCouleur->setMaximumWidth(100);
    editMoyenne->setMaximumWidth(100);
    editVariance->setMaximumWidth(100);
    editEquarType->setMaximumWidth(100);

    Glayout->addWidget(labelMaxCouleur,0, 0);
    Glayout->addWidget(labelMinCouleur, 1, 0);
    Glayout->addWidget(labelMoyenne, 2, 0);
    Glayout->addWidget(labelVariance, 3, 0);
    Glayout->addWidget(labelEquarType, 4, 0);
    Glayout->addWidget(editMaxCouleur, 0, 1);
    Glayout->addWidget(editMinCouleur, 1, 1);
    Glayout->addWidget(editMoyenne, 2, 1);
    Glayout->addWidget(editVariance, 3, 1);
    Glayout->addWidget(editEquarType, 4, 1);

    QFrame * container = new QFrame();
    container->setMinimumSize(700,500);
    QVBoxLayout * frameLayout = new QVBoxLayout(container);
    frameLayout->addWidget(customPlot);


    Glayout->setMargin(0);
    Hlayout->addLayout(Glayout);
    Hlayout->addWidget(container);

    this->setLayout(Hlayout);



    // setup legend:
    customPlot->legend->setVisible(true);
    customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    customPlot->legend->setBrush(QColor(255, 255, 255, 200));

}



