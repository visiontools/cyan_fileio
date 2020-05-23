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
    double R ;
    double G ;
    double B ;

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
        
        // Verifier taille 
        // Verifier que ce n'est pas une image mono
        

        image_resize ( *img, image->rows, image->columns, NULL ) ;  
    }

    buffer = GetAuthenticPixels( image, 0, 0, image->columns, image->rows, exception ) ;
    X = (*img)->X ;
    Y = (*img)->Y ;
    Z = (*img)->Z ;

    for (i=0; i<image->columns; i++ )
        for (j=0; j<image->rows; j++ ) {
            R = (double) *buffer / QuantumRange ;
            buffer++ ;
            G = (double) *buffer / QuantumRange ;
            buffer++ ;
            B = (double) *buffer / QuantumRange ;
            buffer++ ;
            
            RGB_to_XYZ( CYAN_RGB_sRGB, R,G,B, X, Y, Z ) ;
            
            // if ((i==0) && (j==0 )) {
            //     
            //     printf("Read : R = %lf \n", R ) ;
            //     printf("Read : G = %lf \n", G ) ;
            //     printf("Read : B = %lf \n", B ) ;
            //     printf("\n");
            //     printf("Read : X = %lf \n", *X ) ;
            //     printf("Read : Y = %lf \n", *Y ) ;
            //     printf("Read : Z = %lf \n", *Z ) ;
            //     printf("\n");
            // 
            // }
            
            X++ ;
            Y++ ;
            Z++ ;
        }

    // ---

    DestroyImage(image);
    image_info=DestroyImageInfo(image_info);
    exception=DestroyExceptionInfo(exception);
    MagickCoreTerminus();

    return ERR_OK ;
}

