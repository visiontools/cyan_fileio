#include <stdio.h>
#include <cyan/cyan.h>
#include <cyan/fileio/imageio.h>

int main(int argc, char** argv) {

    image_t* img = NULL ;
    
    if ( argc != 3  ) {
        fprintf( stderr, "usage: %s <input_image_file> <output.cyan>\n", argv[0] ) ;
        return -1 ;
    }


    if( image_import( &img, argv[1] ) != ERR_OK ) {
        fprintf( stderr, "Error while opening %s\n", argv[1] ) ;
        return -1 ;
    }

    if (image_save( img, argv[2] ) != ERR_OK ) {
        fprintf( stderr, "Error while writing %s\n", argv[2] ) ;
        return -1 ;
    }
    
    image_free( img ) ;

    return 0 ;

}
