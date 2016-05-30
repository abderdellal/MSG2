#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <QString>

class Image
{
public:
    Image(const char *fichier);
    Image(unsigned short *data, int w, int h);
    Image(unsigned short *data, int dX, int dY, int w, int h);
    Image(QString fichier);
    ~Image();

    int getIntPixel(int x, int y);
    char getCharPixel(int x, int y);
    int getHeight();
    int getWidth();
    void setOffsetX(int ox);
    void setOffsetY(int oy);
    int getOffsetX();
    int getOffsetY();
    unsigned short * getData();
    void save(QString location);
    void saveCompress(QString location);
    Image * crop(int x1, int y1, int x2, int y2);
    Image * negatif();
    Image * contrastStatique();
    Image * difference(Image * image);
    long double correlation(Image * image);

private:
    unsigned short *im;
    int width;
    int height;
    int offsetX;
    int offsetY;
};

#endif
