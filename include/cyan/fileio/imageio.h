#ifndef CYAN_FILEIO_H
#define CYAN_FILEIO_H

#include <cyan/image/image.h>

int image_import( image_t** img, const char* path ) ;
int image_export( image_t* img, const char* path, const char* magick ) ;


#endif
