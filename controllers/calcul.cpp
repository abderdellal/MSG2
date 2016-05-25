#include "calcul.h"

Calcul::Calcul()
{
}

Image * Calcul::NDVI(Image * VIS_06, Image * VIS_08)
{
    unsigned short * im6 = VIS_06->getData();
    unsigned short * im8 = VIS_08->getData();
    int height = VIS_06->getHeight();
    int width = VIS_06->getWidth();
    double ndvi;

    if(VIS_06->getHeight() == VIS_08->getHeight() && VIS_06->getWidth() == VIS_08->getWidth() && VIS_06->getOffsetX() == VIS_08->getOffsetX() && VIS_06->getOffsetY() == VIS_08->getOffsetY())
    {
        unsigned short * ndviMAT = (unsigned short *) malloc(width * height * sizeof(unsigned short)) ;

        for(int i = 0; i < (width*height) - 1; i++)
        {
            if((im8[i]+im6[i]) == 0)
            {
                ndvi = 1;
            }
            else
            {
                ndvi = ((double)im8[i]-im6[i])/((double)im8[i]+im6[i]);
            }
            ndviMAT[i] = (ndvi + 1) * 511.5;
        }

        Image * newImg = new Image(ndviMAT, width, height);
        newImg->setOffsetX(VIS_06->getOffsetX());
        newImg->setOffsetY(VIS_06->getOffsetY());
        return newImg;
    }
    else
    {
        exit(0);
    }
}
