#ifndef FBITBUFFER_H
#define FBITBUFFER_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>

class FBitBuffer
{
public:

    typedef struct {
       unsigned char tampon;
       char * mode;
       int offset;
       FILE * fid;
    } BitBuffer;

    static FBitBuffer::BitBuffer * fopen_bits(const char *fichier, const char *mode);
    static void fclose_bits(BitBuffer * buffer);
    static void fwrite_bits(int val,int nbits,BitBuffer* buffer);
    static int fread_bits(int nbits,BitBuffer* buffer);
};

#endif // FBITBUFFER_H
