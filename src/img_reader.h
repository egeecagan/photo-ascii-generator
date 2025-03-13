#include "img.h"
#ifndef IMG_READER_H
#define IMG_READER_H

char *readfilename(void);
image *readimage(const char *);
void resizeImage(image *);
unsigned char ***returnrgbarray(image *);
unsigned char turntogray(const unsigned char *);
unsigned char ***turntograyscale(image *);

#endif // IMG_READER_H
