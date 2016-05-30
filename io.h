#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/stat.h>
//#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <ctype.h>
#include <iostream>
#include <QString>
#include <QDir>

#include "fbitbuffer.h"


class IO
{
public:
    static unsigned short * getImage(const char * Fichier, int &height, int &width);  //fonction qui permet de récuperer une Image
    static int sauverPGM16(unsigned short *res,const char *fichier,int X,int Y);
    static bool removeDir(const QString & dirName);
    static bool removeFile(const QString & dirName);
    static bool sauverPGM16Compresse(unsigned short *res, const char *fichier, int X, int Y);
    static unsigned short * getImageCompress(const char * fichier, int &height, int &width);  //fonction qui permet de récuperer une Image


private:
    static bool coder(FBitBuffer::BitBuffer * flux, unsigned short * im, int offsetX, int offsetY, int width, int height, int imWidth, int imHeight);
    static bool decoder(FBitBuffer::BitBuffer * flux, unsigned short * im, int offsetX, int offsetY, int width, int height, int imWidth);
};

#endif // IO_H
