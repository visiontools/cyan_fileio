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
            *X = (double) *buffer / QuantumRange ;
            buffer++ ;
            X++ ;
            *Y = (double) *buffer / QuantumRange ;
            buffer++ ;
            Y++ ;
            *Z = (double) *buffer / QuantumRange ;
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


int image_export( image_t* img, const char* path ) {
    
    ExceptionInfo *exception;
    ExceptionInfo *exception2;
    Image *image;
    ImageInfo *image_info;
    double* buffer ;
    int i ;
    int j ;
    
    buffer = (double*) malloc( img->rows*img->cols*3*sizeof(double)) ;

    double* pt_x ;
    double* pt_y ;
    double* pt_z ;

    pt_x = img->X ;
    pt_y = img->Y ;
    pt_z = img->Z ;

    for (j=0; j<img->rows; j++ ) {
        for (i=0; i<img->cols; i++ ) {

        buffer[ 3*(i+j*img->cols) ]   = *pt_x ;
        buffer[ 3*(i+j*img->cols)+1 ] = *pt_y ;
        buffer[ 3*(i+j*img->cols)+2 ] = *pt_z;
        
        pt_x++ ;
        pt_y++ ;
        pt_z++ ;
        
        }
    }

    MagickCoreGenesis( (char*) NULL,MagickTrue);

    exception=AcquireExceptionInfo();
    exception2=AcquireExceptionInfo();
    image_info=CloneImageInfo((ImageInfo *) NULL);
    strcpy(image->filename,path);

    image = ConstituteImage(img->cols,img->rows,"RGB",DoublePixel,buffer, exception);
    if (exception->severity != UndefinedException)
        CatchException(exception);

    image_info->file = fopen ("test.png", "w+b");
    strcpy (image_info->filename, "test.png");
    strcpy (image_info->magick, "png");
    WriteImage( image_info, image, exception2 ) ; 
    fclose( image_info->file ) ;
    if (exception2->severity != UndefinedException)
         CatchException(exception2);

    MagickCoreTerminus();

    free(image) ;

    return ERR_OK ;
}
