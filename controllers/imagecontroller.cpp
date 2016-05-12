#include "imagecontroller.h"


QImage * ImageController::DataToQImage( int width, int height, unsigned short * data )
{
    QImage * image = new QImage( width, height, QImage::Format_ARGB32 );
    int k = 0;
    for ( int i = 0; i < height; ++i )
    {
        for( int j = 0; j < width ; j++)
        {
        QRgb argb = qRgba(((data[k]%1024)/4), //red
                           ((data[k]%1024)/4), //green
                           ((data[k]%1024)/4), //blue
                           255); //alpha
        image->setPixel( j , i, argb );
        k++;
        }
    }
    return image;
}
Image * ImageController::getImage(QString fichier)
{
    std::string s = fichier.toStdString();
    const char * f = s.c_str();
    Image * image = new Image(f);
    return image;
}

QImage * ImageController::getQImage(Image *image)
{
    QImage * qimage;
    unsigned short * im = image->getData();
    qimage = DataToQImage(image->getWidth(), image->getHeight(),im);
    return qimage;
}

QPixmap * ImageController::getPixmap(const char *fichier)
{
    Image * image = getImage(fichier);
    QImage * qimage = getQImage(image);

    QPixmap * pixmap = new QPixmap();
    pixmap->convertFromImage(*qimage);

    delete qimage;
    return pixmap;
}


