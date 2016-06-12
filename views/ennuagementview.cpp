#include "ennuagementview.h"

EnnuagementView::EnnuagementView(QWidget *parent) :
    QWidget(parent)
{

    selectDays = new SelectDayEnnuagement();

    selectDays->show();

    QObject::connect(selectDays, SIGNAL(intervalSelected(QList<QString>,QString)), this, SLOT(calculerEnnuagement(QList<QString>,QString)));
}


void EnnuagementView::calculerEnnuagement(QList<QString> folderList, QString finF)
{
    if(!folderList.empty())
    {

        bool decoup = false;
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

        QList<QString> canalList;
        canalList <<  "IR_120" << "IR_108" << "VIS008";
        QString firstDir = folderList.first().section('/', -2);
        firstDir = firstDir.left(8);
        QString lastDir = folderList.last().section('/', -2);
        lastDir = lastDir.left(8);

        QString EnnuagementDir;
        EnnuagementDir.append(".\\Ennuagement\\");
        EnnuagementDir.append(firstDir);
        EnnuagementDir.append(lastDir);
        QString minDir = EnnuagementDir;
        QString maxDir = EnnuagementDir;
        minDir.append("\\min");
        maxDir.append("\\max");
        QDir maximumDir(maxDir);
        QDir minimumDir(minDir);
        if(!maximumDir.exists())
        {
            maximumDir.mkpath(".");
        }
        if(!minimumDir.exists())
        {
            minimumDir.mkpath(".");
        }


        foreach(QString canal , canalList)
        {
            QList<Image * > imageList;
            QList<QString> EnnuFolderList;

            QString cheminCanal;
            cheminCanal.append(EnnuagementDir);
            cheminCanal.append("\\");
            cheminCanal.append(canal);
            QDir canalDir(cheminCanal);
            if(!canalDir.exists())
            {
                canalDir.mkpath(".");
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
                    EnnuFolderList.append(temp);
                }
                else if(trouve)
                {
                    EnnuFolderList.append(folder.section('/', -1));
                }

            }


            unsigned short * imMax;
            unsigned short * imMin;
            int width = imageList.at(0)->getWidth();
            int height = imageList.at(0)->getHeight();
            imMax = (unsigned short *) malloc(width*height*sizeof(unsigned short));
            imMin = (unsigned short *) malloc(width*height*sizeof(unsigned short));

            for(int x = 0; x < width; x++)
            {
                for(int y = 0 ; y < height; y++)
                {
                    int max = 0;
                    int min = 1024;
                    for(int i = 0; i < imageList.size(); i++)
                    {
                        Image * pic = imageList.at(i);
                        if(pic->getIntPixel(x, y) > max)
                        {
                            max = pic->getIntPixel(x, y);
                        }
                        if(pic->getIntPixel(x, y) < min)
                        {
                            min = pic->getIntPixel(x, y);
                        }
                    }
                    imMax[x * width + y] = max;
                    imMin[x * width + y] = min;
                }
            }

            Image * imgMin = new Image(imMin, width, height);
            Image * imgMax = new Image(imMax, width, height);

            QString cheminMin = minDir;
            cheminMin.append("\\");
            cheminMin.append(canal);
            cheminMin.append(finF);
            cheminMin.append(".pgm");
            QString cheminMax = maxDir;
            cheminMax.append("\\");
            cheminMax.append(canal);
            cheminMax.append(finF);
            cheminMax.append(".pgm");
            imgMin->save(cheminMin);
            imgMax->save(cheminMax);

            for(int i = 0 ; i < imageList.size(); i++)
            {
                unsigned short * ennuIm;
                ennuIm = (unsigned short *) malloc(width*height*sizeof(unsigned short));
                Image * img = imageList.at(i);

                for(int x = 0 ; x < width; x++)
                {
                    for(int y = 0; y < height; y++)
                    {
                        int pixelmin = imgMin->getIntPixel(x,y);
                        int pixelMax = imgMax->getIntPixel(x,y);
                        int pixel = img->getIntPixel(x,y);
                        int val = pixel - pixelmin;
                        int mode = pixelMax - pixelmin;
                        double q = ((double)val) /mode;
                        val = q * 1023;
                        ennuIm[x * width + y] = val;
                    }
                }

                Image * ennuImage = new Image(ennuIm, width, height);

                QString cheminImage;
                cheminImage.append(canalDir.path());
                QString nomFichier;
                nomFichier.append(folderList.at(i).section('/', -2));
                nomFichier = nomFichier.left(8);
                nomFichier.append(".pgm");
                cheminImage.append("\\");
                cheminImage.append(nomFichier);
                cheminImage.replace("/", "\\");

                ennuImage->save(cheminImage);

            }

            selectDays->close();

        }

    }
}
