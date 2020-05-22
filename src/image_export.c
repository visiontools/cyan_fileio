#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <MagickCore/MagickCore.h>

#include <cyan/image/image.h>
#include <cyan/common/error.h>

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
    double R ;
    double G ;
    double B ;

    pt_x = img->X ;
    pt_y = img->Y ;
    pt_z = img->Z ;

    for (j=0; j<img->rows; j++ ) {
        for (i=0; i<img->cols; i++ ) {

        XYZ_to_RGB( CYAN_RGB_sRGB, *pt_x, *pt_y, *pt_z , &R, &G, &B ) ;
        

        buffer[ 3*(i+j*img->cols) ]   = R ;
        buffer[ 3*(i+j*img->cols)+1 ] = G ;
        buffer[ 3*(i+j*img->cols)+2 ] = B ;
        
        pt_x++ ;
        pt_y++ ;
        pt_z++ ;
        
        }
    }

    MagickCoreGenesis( (char*) NULL,MagickTrue);

    exception=AcquireExceptionInfo();
    exception2=AcquireExceptionInfo();
    image_info=CloneImageInfo((ImageInfo *) NULL);

    image = ConstituteImage(img->cols,img->rows,"RGB",DoublePixel,buffer, exception);
    if (exception->severity != UndefinedException)
        CatchException(exception);

    strcpy(image->filename,path);
    
    image_info->file = fopen ("test.png", "w+b");
    strcpy (image_info->filename, "test.png");
    strcpy (image_info->magick, "png");
   
    WriteImage( image_info, image, exception2 ) ; 
    fclose( image_info->file ) ;
    if (exception2->severity != UndefinedException)
         CatchException(exception2);

    MagickCoreTerminus();

    free(image) ;       // FIXME
    // free( buffer ) ; ?

    return ERR_OK ;
}
