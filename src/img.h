#ifndef IMG_H
#define IMG_H

typedef struct img {
    unsigned char *data;
    int width, height; // height - width
    int channels_in_file;
    int desired_channels;
} image;

#endif
