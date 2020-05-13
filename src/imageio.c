#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <MagickCore/MagickCore.h>

#include <cyan/image/image.h>
#include <cyan/common/error.h>


int image_import( image_t** img, char* path ) {

    ExceptionInfo *exception;
    Image *image;
    ImageInfo *image_info;
    Quantum* buffer ;
    int i, j ;
    double* X ;
    double* Y ;
    double* Z ;

    MagickCoreGenesis( (char*) NULL,MagickTrue);
    exception=AcquireExceptionInfo();
    image_info=CloneImageInfo((ImageInfo *) NULL);
    strcpy(image_info->filename,path);
    image=ReadImage(image_info,exception);

    if (exception->severity != UndefinedException)
        CatchException(exception);
    if (image == (Image *) NULL)
        exit(1);

    // ---

    if (*img == NULL ) {
        *img = image_new( image->rows, image->columns ) ;
    } else {
        image_resize ( *img, image->rows, image->columns, NULL ) ;  
    }

    TransformImageColorspace( image, XYZColorspace, exception ) ;
    buffer = GetAuthenticPixels( image, 0, 0, image->columns, image->rows, exception ) ;
    X = (*img)->X ;
    Y = (*img)->Y ;
    Z = (*img)->Z ;

    for (i=0; i<image->columns; i++ )
        for (j=0; j<image->rows; j++ ) {
            *X = (double) *buffer ;
            buffer++ ;
            X++ ;
            *Y = (double) *buffer ;
            buffer++ ;
            Y++ ;
            *Z = (double) *buffer ;
            buffer++ ;
            Z++ ;
        }

    // ---

    DestroyImage(image);
    image_info=DestroyImageInfo(image_info);
    exception=DestroyExceptionInfo(exception);
    MagickCoreTerminus();

    return ERR_OK ;
}


