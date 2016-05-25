
#include "image.h"
#include "IO.h"
#include <QDebug>

Image::Image(const char *fichier)
{
    im = IO::getImage(fichier, height, width);
}

Image::Image(QString fichier)
{
    std::string s = fichier.toStdString();
    const char * c = s.c_str();
    im = IO::getImage(c, height, width);
}


Image::Image(unsigned short *data, int w, int h)
{
    im = data;
    width = w;
    height = h;
    offsetX = 0;
    offsetY = 0;
}

Image::Image(unsigned short *data, int dX, int dY, int w, int h)
{
    im = data;
    width = w;
    height = h;
    offsetX = dX;
    offsetY = dY;
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
        return (char) ((im[x * width + y] % 1024) / 4);
    else
        return 0;
}

int Image::getIntPixel(int x, int y)
{
    if(y < width && x < height)
        return ((im[x * width + y] % 1024));
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

    Image * newImage = new Image(newMat, minX, minY, maxX - minX, maxY - minY);
    return newImage;
}

void Image::save(QString location)
{
    std::string s = location.toStdString();
    const char * c = s.c_str();
    IO::sauverPGM16(im, c, height,width);
}

Image * Image::negatif()
{
    unsigned short * newIm;

    newIm = (unsigned short *) malloc(width*height*sizeof(unsigned short));

    for(int i = 0; i < (height*width) - 1; i++)
    {
        newIm[i] = 1023 - ((im[i]%1024));
    }

    Image * newImg = new Image(newIm, width, height);
    return newImg;
}

Image * Image::contrastStatique()
{
    int min = 0;
    int max = 0;
    unsigned short * contraste;

    contraste = (unsigned short *) malloc(width*height*sizeof(unsigned short));

    for(int i = 0; i < (height*width) - 1; i++)
    {
        if(max < im[i])
            max = im[i];
        if(min > im[i])
            min = im[i];
    }
    for(int i=0;i<(height*width) - 1;i++)
    {
        unsigned short color = (((double)im[i]-(double)min) / ((double)(max-min)))*1024;
        contraste[i]= color;
    }

    Image * newImg = new Image(contraste, width, height);
    return newImg;
}

Image * Image::difference(Image *image)
{
    if(image->getWidth() == width && image->getHeight() == height)
    {
        unsigned short * newIm;
        newIm = (unsigned short *) malloc(width*height*sizeof(unsigned short));

        unsigned short * im2 = image->getData();

        for(int i=0;i<(height*width) - 1;i++)
        {
            unsigned short color = abs(im[i] - im2[i]);
            newIm[i]= color;
        }
        Image * newImg = new Image(newIm, width, height);
        return newImg;
    }
    else
    {
        return image;
    }
}

void Image::setOffsetX(int ox)
{
    offsetX = ox;
}
void Image::setOffsetY(int oy)
{
    offsetY = oy;
}
int Image::getOffsetX()
{
    return offsetX;
}
int Image::getOffsetY()
{
    return offsetY;
}
