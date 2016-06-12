#include "correlationtempview.h"

CorrelationTempView::CorrelationTempView(QWidget *parent) :
    QWidget(parent)
{
    selectInterval = new SelectDayInterval();

    selectInterval->show();

    QObject::connect(selectInterval, SIGNAL(intervalSelected(QList<QString>,QString,QString)), this, SLOT(calculerCorrelation(QList<QString>,QString,QString)));

}


void CorrelationTempView::calculerCorrelation(QList<QString> folderList, QString finF, QString canal)
{
    if(!folderList.empty())
    {
        bool decoup = false;
        QList<Image * > imageList;
        QList<QString> labelList;
        QString first = folderList.at(0);
        first = first.section("/", -1);
        if(first.startsWith("decoupage"))
        {
            decoup = true;
        }
        else
        {
            decoup = false;
        }
        foreach(QString folder, folderList)
        {
            QDir dir(folder);
            bool trouve = false;

            QDirIterator it(dir);
            do
            {
                it.next();
                QString fichier = it.fileName();

                if (fichier.startsWith(canal) && (fichier.endsWith(finF + ".pgm") || fichier.endsWith(finF + ".pgmc")))
                {
                    Image * image = ImageController::getImage(it.filePath());
                    imageList.append(image);
                    trouve = true;
                }
            }while(it.hasNext());

            if(decoup && trouve)
            {
                QString temp = folder.section('/', -2);
                temp = temp.left(8);
                labelList.append(temp);
            }
            else if(trouve)
            {
                labelList.append(folder.section('/', -1));
            }

        }

        QGridLayout * Glayout = new QGridLayout();

        int i = 1;
        foreach(QString label, labelList)
        {
            QLabel * qlabel = new QLabel(label);
            qlabel->setMargin(10);
            Glayout->addWidget(qlabel, 0, i);
            i++;
        }

        i = 1;
        foreach(Image * img, imageList)
        {
            QString jour = labelList.at(i - 1);
            QLabel * qlabel = new QLabel(jour);
            qlabel->setMargin(10);
            Glayout->addWidget(qlabel, i, 0);

            int j = 1;
            foreach(Image * img2, imageList)
            {
                double correlation = img->correlation(img2);
                QString stringCorr = (new QString())->number(correlation);

                QLabel * labelCorr = new QLabel(stringCorr);
                labelCorr->setMargin(10);
                Glayout->addWidget(labelCorr, i, j);

                j++;
            }
            i++;
        }
        this->setLayout(Glayout);
        selectInterval->close();

    }
}
