#include "fbitbuffer.h"


FBitBuffer::BitBuffer * FBitBuffer::fopen_bits(const char * fichier,const char * mode) {
  BitBuffer * buffer;
  buffer = (BitBuffer*) malloc(sizeof(BitBuffer));
  buffer->tampon = 0;
  buffer->offset=0;
  buffer->fid = fopen(fichier,mode);
  if (!buffer->fid) {
     free(buffer);
     return NULL;
  }
  buffer->mode = (char*) malloc(strlen(mode)+1);
  strcpy(buffer->mode,mode);
  return buffer;
}

void FBitBuffer::fclose_bits(BitBuffer * buffer) {
   if (!strcmp(buffer->mode,"wb") && buffer->offset) {
      fwrite(&(buffer->tampon),1,1,buffer->fid);
   }
   fclose(buffer->fid);
   free(buffer->mode);
   free(buffer);
}

void FBitBuffer::fwrite_bits(int val,int nbits,BitBuffer* buffer) {
   int reste;
   if (buffer->offset+nbits<8) {
      buffer->tampon += (val)<<(buffer->offset);
      buffer->offset+=nbits;
   }
   else
   {
      reste = (val)>>(8-buffer->offset);
      buffer->tampon += ((val)&((1<<(8-buffer->offset))-1))<<(buffer->offset);
      fwrite(&(buffer->tampon),1,1,buffer->fid);
      nbits -= (8-buffer->offset);
      buffer->tampon = 0;
      buffer->offset = 0;
      fwrite_bits(reste,nbits,buffer);
   }
}

int FBitBuffer::fread_bits(int nbits,BitBuffer* buffer) {
   int reste,sup;
   int bitslus;
   int resultat;
   if (nbits==0) {
      return 0;
   }
   if (buffer->offset==0) {
      fread(&(buffer->tampon),1,1,buffer->fid);
   }
   if (buffer->offset+nbits<8) {
      resultat =  (buffer->tampon>>buffer->offset)&((1<<nbits)-1);
      buffer->offset+=nbits;
      return resultat;
   }
   else
   {
      reste = (buffer->tampon>>buffer->offset)&((1<<(8-buffer->offset))-1);
      nbits -= (8-buffer->offset);
      bitslus = (8-buffer->offset);
      buffer->tampon = 0;
      buffer->offset = 0;
      sup = fread_bits(nbits,buffer)<<bitslus;
      return reste+sup;
   }
}
