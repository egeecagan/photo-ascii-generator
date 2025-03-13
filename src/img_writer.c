#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "img_writer.h"
#include "img_reader.h"
#include "img.h"

//const char* density = "N@#W$9876543210?!abc;:+=-,._ ";
const char* density = " _.,-=+:;cba!?0123456789$W#@N";

char turntonetochar(unsigned char colorvalue) {
    int density_length = strlen(density);
    int index = ((255 - colorvalue) * 28) / 255;
    return density[index];
}

void printer(image *imageptr, char *filename) {

    unsigned char ***graymatrix = turntograyscale(imageptr);

    FILE *textfile = fopen(filename, "w");

    int length = imageptr->width;
    int height = imageptr->height;
    printf("length : %d - height : %d\n",length, height);

    for (int i = 0; i < length; i++) {
        for(int k = 0; k < height; k++) {
            unsigned char grayvalue = graymatrix[k][i][0];  
            char charactervalue = turntonetochar(grayvalue);
            fputc(charactervalue, textfile);
        }
        fputc('\n', textfile);
    }
}
