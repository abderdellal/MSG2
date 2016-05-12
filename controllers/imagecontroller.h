
#include "image.h"

#include <QPixmap>
#include <QImage>


class ImageController
{
public:
    static QPixmap * getPixmap(const char * fichier);
    static QImage * getQImage(Image * image);
    static Image * getImage(QString fichier);

private :
    static QImage * DataToQImage( int width, int height, unsigned short *data );
};

