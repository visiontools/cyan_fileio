#include <stdio.h>
#include <cyan/image/image.h>
#include <cyan/fileio/imageio.h>


int main( int argc, char** argv, char* envv ) {

    image_t* image = NULL ; 
   
    image_import( &image, argv[1] ) ;

    image_save( image, argv[2] ) ;

    return 0 ;
}

