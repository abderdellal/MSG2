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
    //std::string s = fichier.toStdString();
    //const char * f = s.c_str();
    Image * image = new Image(fichier);
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

QImage * ImageController::getQImage(Image *image1, Image *image2)
{
    unsigned short * data = image1->getData();
    unsigned short * data2 = image2->getData();
    int width = image1->getWidth();
    int height = image1->getHeight();
    QImage * qimage = new QImage( width, height, QImage::Format_ARGB32 );

    int k = 0;
    for ( int i = 0; i < height; ++i )
    {
        for( int j = 0; j < width ; j++)
        {
        QRgb argb = qRgba(((data[k]%1024)/4), //red
                           ((data2[k]%1024)/4), //green
                           0, //blue
                           255); //alpha
        qimage->setPixel( j , i, argb );
        k++;
        }
    }
    return qimage;
}

QImage * ImageController::getQImage(Image *image1, Image *image2, Image *image3)
{
    unsigned short * data = image1->getData();
    unsigned short * data2 = image2->getData();
    unsigned short * data3 = image3->getData();
    int width = image1->getWidth();
    int height = image1->getHeight();
    QImage * qimage = new QImage( width, height, QImage::Format_ARGB32 );

    int k = 0;
    for ( int i = 0; i < height; ++i )
    {
        for( int j = 0; j < width ; j++)
        {
        QRgb argb = qRgba(((data[k]%1024)/4), //red
                           ((data2[k]%1024)/4), //green
                           ((data3[k]%1024)/4), //blue
                           255); //alpha
        qimage->setPixel( j , i, argb );
        k++;
        }
    }
    return qimage;
}

