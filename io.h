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

class IO
{
public:
    static unsigned short * getImage(const char * Fichier, int &height, int &width);  //fonction qui permet de récuperer une Image
    static int sauverPGM16(unsigned short *res,const char *fichier,int X,int Y);
    static bool removeDir(const QString & dirName);
    static bool removeFile(const QString & dirName);
};

#endif // IO_H
