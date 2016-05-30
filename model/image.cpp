
#include "image.h"
#include "IO.h"
#include <QDebug>
/*
Image::Image(const char *fichier)
{
    im = IO::getImage(fichier, height, width);
}
*/
Image::Image(QString fichier)
{
    std::string s = fichier.toStdString();
    const char * c = s.c_str();
    if(fichier.endsWith(".pgm"))
    {
    im = IO::getImage(c, height, width);
    }
    else if(fichier.endsWith(".pgmc"))
    {
        im = IO::getImageCompress(c, height, width);
    }
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

void Image::saveCompress(QString location)
{
    std::string s = location.toStdString();
    const char * c = s.c_str();
    IO::sauverPGM16Compresse(im, c, height,width);
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
        unsigned short color = (((double)im[i]-(double)min) / ((double)(max-min)))*1023;
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

long double Image::correlation(Image *image)
{
    if(image->getWidth() == width && image->getHeight() == height)
    {
        unsigned short * im2;
        im2 = image->getData();
        long double moy1, moy2, somme1, somme2;
        somme1 = 0;
        somme2 = 0;
        for(int i = 0; i < (height * width) - 1; i++)
        {
            somme1 = somme1 + im[i];
            somme2 = somme2 + im2[i];
        }
        moy1 = somme1/(height * width);
        moy2 = somme2/(height * width);

        double cov = 0;
        long double covariance = 0;

        for(int i = 0; i < (height * width) - 1; i++)
        {
            cov=(im[i]-moy1)*(im2[i]-moy2);
            covariance=covariance+cov;
        }

        double var = 0;
        long double variance1 = 0;
        long double variance2 = 0;

        for(int i = 0; i < (height * width) - 1; i++)
        {
            var = pow((im[i] - moy1),2);
            variance1 = variance1 + var;
            var = pow((im2[i] - moy2),2);
            variance2 = variance2 + var;
        }

        long double cor = covariance /(sqrt(variance1) * sqrt(variance2));
        return cor;
    }
    else
    {
        exit(0);
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
