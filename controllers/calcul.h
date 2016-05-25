#ifndef CALCUL_H
#define CALCUL_H

#include "image.h"

class Calcul
{
public:
    Calcul();
    static Image * NDVI(Image * VIS_06,Image * VIS_08);
};

#endif // CALCUL_H
