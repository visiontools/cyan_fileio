#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <MagickCore/MagickCore.h>

#include <cyan/image/image.h>
#include <cyan/common/error.h>

int image_export( image_t* img, const char* path, const char* magick ) {
    
    ExceptionInfo *exception = NULL ;
    ImageInfo *image_info = NULL ;
    Image *image = NULL ;
    int i ;
    int j ;
    double* buffer = NULL ;
    double* pt_x = NULL ;
    double* pt_y = NULL ;
    double* pt_z = NULL ;
    double R ;
    double G ;
    double B ;

    if ( img == (image_t*) NULL ) {
        CYAN_ERROR( ERR_NULL ) ;
        return ERR_NULL ;
    }

    MagickCoreGenesis( (char*) NULL,MagickTrue);
    
    exception=AcquireExceptionInfo();
    if ( exception == NULL ) {
            CYAN_ERROR( ERR_MALLOC ) ;
            return ERR_MALLOC ;
    }

    image_info=CloneImageInfo((ImageInfo *) NULL);
    if ( image_info == NULL ) {
            CYAN_ERROR( ERR_MALLOC ) ;
            return ERR_MALLOC ;
    }

    image_info->file = fopen (path, "w+b");
    strcpy (image_info->filename, path);
    strcpy (image_info->magick, magick);
    
    if ( !img->monochrome ) {

        buffer = (double*) malloc( img->rows*img->cols*3*sizeof(double)) ;
        if ( buffer == NULL ) {
            CYAN_ERROR( ERR_MALLOC ) ;
            return ERR_MALLOC ;
        }
        
        pt_x = img->X ;
        pt_y = img->Y ;
        pt_z = img->Z ;

        for (j=0; j<img->rows; j++ ) {
            for (i=0; i<img->cols; i++ ) {

            XYZ_to_RGB( CYAN_RGB_sRGB, *pt_x, *pt_y, *pt_z , &R, &G, &B ) ;
            
            // if ((i==0) && (j==0 )) {
            //     
            //     printf("Write : X = %lf \n", *pt_x ) ;
            //     printf("Write : Y = %lf \n", *pt_y ) ;
            //     printf("Write : Z = %lf \n", *pt_z ) ;
            //     printf("\n");
            //     printf("Write : R = %lf \n", R ) ;
            //     printf("Write : G = %lf \n", G ) ;
            //     printf("Write : B = %lf \n", B ) ;
            // 
            // }
        
            buffer[ 3*(i+j*img->cols) ]   = R ;
            buffer[ 3*(i+j*img->cols)+1 ] = G ;
            buffer[ 3*(i+j*img->cols)+2 ] = B ;
        
            pt_x++ ;
            pt_y++ ;
            pt_z++ ;
        
           }
       }

        image = ConstituteImage(img->cols,img->rows,"RGB",DoublePixel,buffer, exception);
        if (exception->severity != UndefinedException) {
            CatchException(exception);
        }
        if ( image == NULL ) {
            CYAN_ERROR( ERR_MALLOC ) ;
            return ERR_MALLOC ;
        }

        strcpy(image->filename,path);
       
        WriteImage( image_info, image, exception ) ; 
        if (exception->severity != UndefinedException)
             CatchException(exception);
        
        fclose( image_info->file ) ;
    
        free(buffer) ;     

    } else {
        
        // img is monochrome

        image = ConstituteImage(img->cols,img->rows,"I",DoublePixel, img->Y, exception);
        if (exception->severity != UndefinedException) {
            CatchException(exception);
        }
        if ( image == NULL ) {
            CYAN_ERROR( ERR_MALLOC ) ;
            return ERR_MALLOC ;
        }

        strcpy(image->filename,path);
       
        WriteImage( image_info, image, exception ) ; 
        if (exception->severity != UndefinedException)
             CatchException(exception);
        
        fclose( image_info->file ) ;
    }

    image=DestroyImage(image);
    image_info=DestroyImageInfo(image_info);
    exception=DestroyExceptionInfo(exception);

    MagickCoreTerminus();


    return ERR_OK ;
}
