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

bool IO::removeDir(const QString & dirName)
{
    bool result = true;
    QDir dir(dirName);

    if (dir.exists()) {
        Q_FOREACH(QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst)) {
            if (info.isDir()) {
                result = removeDir(info.absoluteFilePath());
            }
            else {
                result = QFile::remove(info.absoluteFilePath());
            }

            if (!result) {
                return result;
            }
        }
        result = dir.rmdir(dirName);
    }
    return result;
}

bool IO::removeFile(const QString &dirName)
{
    QFile file (dirName);
    return file.remove();
}







bool IO::sauverPGM16Compresse(unsigned short *im, const char *fichier, int X, int Y)
{
    FILE *fich;

    fich=fopen(fichier,"wb");

    if (!fich)
    {
        printf("Failed to open file\n");
    }
    else
    {
        fprintf(fich,"P5\n");
        fprintf(fich,"%d %d\n",X,Y);
        fprintf(fich,"%d\n",65535);
    }

    FBitBuffer::BitBuffer * flux;
    flux = (FBitBuffer::BitBuffer*) malloc(sizeof(FBitBuffer::BitBuffer));
    flux->fid = fich;
    flux->tampon = 0;
    flux->offset = 0;
    flux->mode = (char*) malloc(strlen("wb")+1);
    strcpy(flux->mode,"wb");

    if(!flux)
    {
        return 0;
    }
    else
    {
        IO::coder(flux, im, 0, 0, Y, X, Y, X);
        FBitBuffer::fclose_bits(flux);
    }
    return 0;
}

bool IO::coder(FBitBuffer::BitBuffer * flux, unsigned short * im, int offsetX, int offsetY, int width, int height, int imWidth, int imHeight)
{

    if(width < 1 || height < 1)
    {
        //do nothing ;)
    }
    else if(width == 1 && height == 1)
    {
        FBitBuffer::fwrite_bits(1, 1, flux);
        FBitBuffer::fwrite_bits(im[(offsetY*imWidth)+offsetX], 10, flux);
    }
    else if(width > 1 || height > 1)
    {
        bool monoChrome = true;
        int color = im[(offsetY*imWidth)+offsetX] % 1024;
        for(int i = offsetY; (i < offsetY + height) && monoChrome; i++)
        {
            for(int j = offsetX ; (j < offsetX + width) && monoChrome; j++)
            {
                if(im[(i*imWidth) + j] % 1024 != color)
                {
                    //int colortemp = im[(i*imWidth) + j];
                    monoChrome = false;
                }
            }
        }

        if(monoChrome)
        {
            FBitBuffer::fwrite_bits(1, 1, flux);
            FBitBuffer::fwrite_bits(color, 10, flux);
        }
        else
        {
            FBitBuffer::fwrite_bits(0, 1, flux);

            int cutX = ceil(((double)offsetX*2 + width)/2);
            int cutY = ceil(((double)offsetY*2 + height)/2);

            coder(flux, im, offsetX, offsetY, width - (width/2), height -(height/2), imWidth, imHeight);
            coder(flux, im, cutX, offsetY, width/2, height - (height/2), imWidth, imHeight);
            coder(flux, im, offsetX, cutY, width - (width/2), height/2, imWidth, imHeight);
            coder(flux, im, cutX, cutY, width/2, height/2, imWidth, imHeight);
        }
    }
    return true;
}

unsigned short * IO::getImageCompress(const char * fichier, int &height, int &width)  //fonction qui permet de récuperer une Image
{
    int DIMX, DIMY;

    char tampon[256];
    int c;
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

    FBitBuffer::BitBuffer * flux;
    flux = (FBitBuffer::BitBuffer*) malloc(sizeof(FBitBuffer::BitBuffer));
    flux->fid = fich;
    flux->tampon = 0;
    flux->offset = 0;
    flux->mode = (char*) malloc(strlen("rb")+1);
    strcpy(flux->mode,"rb");
    im=(unsigned short *)malloc(DIMX*DIMY*sizeof(unsigned short));
    decoder(flux, im, 0, 0, DIMY, DIMX, DIMY);

    width = DIMY;
    height = DIMX;

    FBitBuffer::fclose_bits(flux);

    return im;
}

 bool IO::decoder(FBitBuffer::BitBuffer * flux, unsigned short * im, int offsetX, int offsetY, int width, int height, int imWidth)
{
    if(width < 1 || height < 1)
    {
        //do nothing ;)
    }
    else if(width == 1 && height == 1)
    {
        bool ok = ((bool)FBitBuffer::fread_bits(1, flux));
        int color = FBitBuffer::fread_bits(10, flux);
        im[(offsetY*imWidth) + offsetX] = color;
        if(!ok)
        {
            std::cout << "errer" << std::endl;
        }
    }
    else
    {
        bool monoChrome = ((bool)FBitBuffer::fread_bits(1, flux));
        if(monoChrome)
        {
            int color = FBitBuffer::fread_bits(10, flux);
            for(int i = offsetY; (i < offsetY + height); i++)
            {
                for(int j = offsetX ; (j < offsetX + width); j++)
                {
                    im[(i*imWidth) + j] = (unsigned short) color;
                }
            }
        }
        else
        {
            int cutX = ceil(((double)offsetX*2 + width)/2);
            int cutY = ceil(((double)offsetY*2 + height)/2);

            /*if(width == 1)
            {
                decoder(flux, im, offsetX, offsetY, width - (width/2), height -(height/2), imWidth);
                decoder(flux, im, offsetX, cutY, width - (width/2), height/2, imWidth);
            }
            else if(height == 1)
            {
                decoder(flux, im, offsetX, offsetY, width - (width/2), height -(height/2), imWidth);
                decoder(flux, im, cutX, offsetY, width/2, height - (height/2), imWidth);
            }*/
            //else
            //{
                decoder(flux, im, offsetX, offsetY, width - (width/2), height -(height/2), imWidth);
                decoder(flux, im, cutX, offsetY, width/2, height - (height/2), imWidth);
                decoder(flux, im, offsetX, cutY, width - (width/2), height/2, imWidth);
                decoder(flux, im, cutX, cutY, width/2, height/2, imWidth);
            //}
        }

    }


    return true;
}
