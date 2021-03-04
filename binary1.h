#include <cstdio>
using namespace std;

struct BFILE
{
  FILE* file;

  BFILE(FILE* f)
  {
    file = f;
  }
};

BFILE* openBinaryFileWrite(const char* filename);
void   writeBit(BFILE* f, int b);
void   writeByte(BFILE* f, int b);
void   closeBinaryFileWrite(BFILE*& f);

BFILE* openBinaryFileRead(const char* filename);
int    readBit(BFILE* f);
int    readByte(BFILE* f);
void   closeBinaryFileRead(BFILE*& f);