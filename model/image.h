#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <QString>

class Image
{
public:
    Image(const char *fichier);
    Image(unsigned short *data, int w, int h);
    Image(QString fichier);
    ~Image();
    int getIntPixel(int x, int y);
    char getCharPixel(int x, int y);
    int getHeight();
    int getWidth();
    unsigned short * getData();
    void save(QString location);
    Image * crop(int x1, int y1, int x2, int y2);

private:
    unsigned short *im;
    int width;
    int height;
};

#endif
