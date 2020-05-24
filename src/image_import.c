#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <MagickCore/MagickCore.h>

#include <cyan/image/image.h>
#include <cyan/common/error.h>

void sRGB_convert( Image* image, double**X, double**Y, double **Z, Quantum** Buffer ) ;
void GRAY_convert( Image* image, double**X, double**Y, double **Z, Quantum** Buffer ) ;


int image_import( image_t** img, char* path ) {

    ExceptionInfo *exception;
    Image *image;
    ImageInfo *image_info;
    Quantum* buffer ;
    int i, j ;
    double* X ;
    double* Y ;
    double* Z ;
    double R ;
    double G ;
    double B ;
    void (*fct_convert)(Image*,double**,double**,double**,Quantum**) ;

    ColorspaceType colorspace ;
    int monochrome = 0 ;
    
    MagickCoreGenesis( (char*) NULL,MagickTrue);
    
    exception=AcquireExceptionInfo();
    
    image_info=CloneImageInfo((ImageInfo *) NULL);
    strcpy(image_info->filename,path);
    
    image=ReadImage(image_info,exception);
    if (exception->severity != UndefinedException)
        CatchException(exception);
    if (image == (Image *) NULL) {
        CYAN_ERROR( ERR_MALLOC ) ;
        return ERR_MALLOC ;
    }

    // --- 

    colorspace = GetImageColorspaceType( image, exception) ;
    if (exception->severity != UndefinedException)
        CatchException(exception);

    printf("Cols: %ld \n", image->columns ) ;
    printf("Rows: %ld \n", image->rows ) ;
    printf("Colorspace: %d \n", colorspace ) ;

    switch( colorspace ) {
        case sRGBColorspace:
            monochrome=0 ;
            fct_convert = sRGB_convert ;
            break ;
        case xyYColorspace:
            CYAN_ERROR( ERR_NOT_IMPLEMENTED ) ;     // TODO
            return ERR_NOT_IMPLEMENTED ;
            break ;
        case XYZColorspace: 
            CYAN_ERROR( ERR_NOT_IMPLEMENTED ) ;     // TODO
            return ERR_NOT_IMPLEMENTED ;
            break ;
        case LabColorspace:
            CYAN_ERROR( ERR_NOT_IMPLEMENTED ) ;     // TODO
            return ERR_NOT_IMPLEMENTED ;
            break ;
        case LCHabColorspace:   
            CYAN_ERROR( ERR_NOT_IMPLEMENTED ) ;     // TODO
            return ERR_NOT_IMPLEMENTED ;
            break ;
        case LuvColorspace:
            CYAN_ERROR( ERR_NOT_IMPLEMENTED ) ;     // TODO
            return ERR_NOT_IMPLEMENTED ;
            break ;
        case LCHuvColorspace:
            CYAN_ERROR( ERR_NOT_IMPLEMENTED ) ;     // TODO
            return ERR_NOT_IMPLEMENTED ;
            break ;
        case GRAYColorspace:
            monochrome=1 ;
            fct_convert = GRAY_convert ;
            break ;
        default:
            CYAN_ERROR( ERR_NOT_IMPLEMENTED ) ; 
            return ERR_NOT_IMPLEMENTED ;
            break ;
    }

    // ---

    if (*img == NULL ) {
        *img = image_new( image->columns, image->rows, monochrome ) ;
    } else {
       image_strip_data( *img ) ;
       if (((*img)->rows!=image->rows)||((*img)->cols!=image->columns)||((*img)->monochrome!=monochrome))
            image_resize ( *img, image->columns, image->rows, monochrome, NULL ) ;  
    }

    buffer = GetAuthenticPixels( image, 0, 0, image->columns, image->rows, exception ) ;

    X = (*img)->X ;
    Y = (*img)->Y ;
    Z = (*img)->Z ;

    for (i=0; i<image->columns; i++ )
        for (j=0; j<image->rows; j++ ) {
            fct_convert( image, &X,&Y,&Z,&buffer) ;
        }

    // ---

    DestroyImage(image);
    image_info=DestroyImageInfo(image_info);
    exception=DestroyExceptionInfo(exception);
    MagickCoreTerminus();

    return ERR_OK ;
}

void sRGB_convert( Image* image, double**X, double**Y, double **Z, Quantum **buffer) {
            double R ;
            double G ;
            double B ;
            R = (double) **buffer / QuantumRange ;
            (*buffer)++ ;
            G = (double) **buffer / QuantumRange ;
            (*buffer)++ ;
            B = (double) **buffer / QuantumRange ;
            (*buffer)++ ;
            RGB_to_XYZ( CYAN_RGB_sRGB, R,G,B, *X, *Y, *Z ) ;
            (*X)++ ;
            (*Y)++ ;
            (*Z)++ ;
}

void GRAY_convert( Image* image, double**X, double**Y, double **Z, Quantum **buffer) {
            **Y = (double) **buffer / QuantumRange ;
            (*buffer)++ ;
            (*Y)++ ;
}
