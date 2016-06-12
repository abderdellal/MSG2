#ifndef IMAGECONTROLLER_H
#define IMAGECONTROLLER_H

#include "image.h"

#include <QPixmap>
#include <QImage>


class ImageController
{
public:
    static QPixmap * getPixmap(const char * fichier);
    static QImage * getQImage(Image * image);
    static QImage * getQImage(Image * image1, Image * image2);
    static QImage * getQImage(Image * image1, Image * image2, Image * image3);
    static Image * getImage(QString fichier);

private :
    static QImage * DataToQImage( int width, int height, unsigned short *data );
};

#endif // IMAGECONTROLLER_H
