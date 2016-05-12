
#include "image.h"
#include "IO.h"


Image::Image(const char *fichier)
{
    //LecteurPGM * lecteur = new LecteurPGM();
    im = IO::getImage(fichier, height, width);
}

Image::Image(unsigned short *data, int w, int h)
{
    im = data;
    width = w;
    height = h;
}


Image::~Image()
{
    delete im;
}

unsigned short * Image::getData()
{
    return im;
}

int Image::getHeight()
{
    return height;
}

int Image::getWidth()
{
    return width;
}

char Image::getCharPixel(int x, int y)
{
    if(y < width && x < height)
        return (char) 256 -  ((im[x * width + y] % 1024) / 4);
    else
        return 0;
}

int Image::getIntPixel(int x, int y)
{
    if(y < width && x < height)
        return ((im[x * width + y] % 1024) / 4);
    else
        return 0;
}

Image * Image::crop(int x1, int y1, int x2, int y2)
{
    int taille = std::abs(x1 - x2) * std::abs(y1 - y2);
    unsigned short * oldMat = im;
    unsigned short * newMat = (unsigned short *)malloc(taille*sizeof(unsigned short));
    int minX = (x1>x2)?x2:x1;
    int maxX = (x1>x2)?x1:x2;
    int minY = (y1>y2)?y2:y1;
    int maxY = (y1>y2)?y1:y2;

    int k = 0;
    for(int i = minY; i < maxY; i++)
    {
        for(int j = minX; j < maxX; j++)
        {
            newMat[k] = oldMat[i * getWidth() + j];
            k++;
        }
    }

    Image * newImage = new Image(newMat, maxX - minX, maxY - minY);
    return newImage;
}

void Image::save(QString location)
{
    std::string s = location.toStdString();
    const char * c = s.c_str();
    IO::sauverPGM16(im, c, height,width);
}
