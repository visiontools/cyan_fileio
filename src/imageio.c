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





    // ---

    DestroyImage(image);
    image_info=DestroyImageInfo(image_info);
    exception=DestroyExceptionInfo(exception);
    MagickCoreTerminus();

    return ERR_OK ;
}


