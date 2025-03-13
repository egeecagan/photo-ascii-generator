#include "img_reader.h"
#include "img.h"

#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "../libs/stb_image_resize2.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../libs/stb_image.h"



char *readfilename(void) {
    char *filename;
    filename = (char *) malloc(256 * sizeof(char));
    if (filename == NULL) {
        fprintf(stderr, "memory allocation failed for filename\n");
        return NULL;
    }
    printf("enter the file name : ");
    scanf("%255s",filename);
    return filename;
}

image *readimage(const char *filename) {
    stbi_set_flip_vertically_on_load(1);
    image *imagePtr;
    imagePtr = (image *)malloc(sizeof(image));
    if (!imagePtr) {
        fprintf(stderr, "memory allocation error for image\n");
        free(imagePtr);
        return NULL;
    }
    imagePtr->data = stbi_load(filename, &imagePtr->width, &imagePtr->height, &imagePtr->channels_in_file, 3);

    if (imagePtr->data == NULL) {
        printf("image could not load %s\n", filename);
        free(imagePtr); 
        return NULL;
    }
    return imagePtr;
}

void resizeImage(image *imageptr) {
    int width = imageptr->width;
    int height = imageptr->height;
    int channels = imageptr->channels_in_file;

    int magicnumber = 100;

    double ratio = (double) width / height;
    int newwidth, newheight;

    if (ratio == 1) {
        newwidth  = magicnumber;
        newheight = magicnumber;
    } else if (ratio < 1) {
        newheight = magicnumber;
        newwidth = (int)(ratio * newheight);
    } else {
        newwidth = magicnumber;
        newheight = (int)(newwidth / ratio);
    }

    unsigned char* resized_data = (unsigned char*)malloc(newwidth * newheight * channels);
    if (!resized_data) {
        fprintf(stderr, "memory allocation failed\n");
        return;
    }

    stbir_resize_uint8_linear(imageptr->data, width, height, 0, resized_data, newwidth, newheight, 0, channels);

    free(imageptr->data);

    imageptr->data = resized_data;
    imageptr->width = newwidth;
    imageptr->height = newheight;
}

unsigned char ***returnrgbarray(image *imageptr) {
    int width = imageptr->width;
    int height = imageptr->height;
    int channels = imageptr->channels_in_file;

    unsigned char ***matrix = (unsigned char ***)malloc(height * sizeof(unsigned char **));
    for (int i = 0; i < height; i++) {
        matrix[i] = (unsigned char **)malloc(width * sizeof(unsigned char *));
        for (int j = 0; j < width; j++) {
            matrix[i][j] = (unsigned char *)malloc(3 * sizeof(unsigned char)); 
        }
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int index = (y * width + x) * channels;  
            matrix[y][x][0] = imageptr->data[index];  
            matrix[y][x][1] = imageptr->data[index + 1]; 
            matrix[y][x][2] = imageptr->data[index + 2]; 
        }
    }
    return matrix;

}

unsigned char turntogray(const unsigned char *ar) {
    unsigned char returnvalue = (unsigned char)(ar[0] * 0.299 + ar[1] * 0.587 + ar[2] * 0.114);
    return returnvalue;
}

unsigned char ***turntograyscale(image *imageptr) {
    unsigned char ***rgbarray = returnrgbarray(imageptr);
    unsigned char ***graymatrix = (unsigned char***)malloc(sizeof(unsigned char**) * imageptr->height);
    for (int i = 0; i < imageptr->height; i++) {
        graymatrix[i] = (unsigned char**)malloc(sizeof(unsigned char*) * imageptr->width);
        for(int j = 0; j < imageptr->width; j++) {
            graymatrix[i][j] = (unsigned char*)malloc(sizeof(unsigned char) * 1);  
        }
    }
    for (int i = 0; i < imageptr->height; i++) {
        for (int j = 0; j < imageptr->width; j++) {
            unsigned char *pixel = rgbarray[i][j];
            unsigned char tone = turntogray(pixel);
            graymatrix[i][j][0] = tone;
        }
    }
    return graymatrix;
}
