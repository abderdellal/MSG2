#include "io.h"


using namespace std;

unsigned short * IO::getImage(const char * fichier, int &height, int &width)
{
    int DIMX, DIMY;

    char tampon[256];
    int i,j,c;
    FILE *fich;

    unsigned short *im;

    fich = fopen(fichier, "rb");

    fscanf(fich,"P%d\n",&c);

    do
        fgets(tampon,256,fich);
    while ( tampon[0]=='#' );

    sscanf(tampon,"%d %d",&DIMX,&DIMY);

    fscanf(fich,"%d\n",&c);

    if (c>65535)
    {
        printf("PROBLEME DE PROFONDEUR MAXIMALE\n");
        exit(0);
    }

    im=(unsigned short *)malloc(DIMX*DIMY*sizeof(unsigned short));

        int N = DIMX * DIMY - 1;
        for (i=0;i<DIMY;i++)
        {
            for (j=0;j<DIMX;j++)
            {
                im[N - (i*DIMX+j)]=getc(fich)*256+getc(fich);
            }
        }


    width = DIMY;
    height = DIMX;
    fclose(fich);

    return im;
}


int IO::sauverPGM16(unsigned short *res, const char *fichier, int X, int Y)
{
    FILE *fich;
    int i;
    unsigned char q,r;

    fich=fopen(fichier,"wb");
    //fich = fopen(".\\decoupe\\20120528\\IR_016201205280530(2750-565-766-891).pgm","wb");
    if (!fich)
    {
        printf("Failed to open file\n");
    }
    else
    {
        fprintf(fich,"P5\n");
        fprintf(fich,"%d %d\n",X,Y);
        fprintf(fich,"%d\n",65535);
        int N = (Y * X) -1;
        for (i=0;i<Y*X;i++)
        {
            q=floor(res[N - i]/256.);
            r=res[N - i]%256;
            putc(q,fich);
            putc(r,fich);
        }

        fclose(fich);
    }
    return 0;
}
