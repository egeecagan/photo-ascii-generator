#include <stdio.h>
#include "img_reader.h"
#include "img_writer.h"
#include "img.h"

int main(int argc, char** argv) {

char  *imagename = readfilename();
image *img       = readimage(imagename);
resizeImage(img);
printer(img, "output.txt");
    
}
