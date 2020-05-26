#include <stdio.h>
#include <cyan/cyan.h>
#include <cyan/fileio/imageio.h>

int main(int argc, char** argv) {

    image_t* img = NULL ;
    
    if ( argc != 4  ) {
        fprintf( stderr, "usage: %s <input_image_file> \"<type>\" <output.cyan>\n", argv[0] ) ;
        return -1 ;
    }


    if( image_load( &img, argv[1] ) != ERR_OK ) {
        fprintf( stderr, "Error while opening %s\n", argv[1] ) ;
        return -1 ;
    }

    if (image_export( img, argv[3], argv[2] ) != ERR_OK ) {
        fprintf( stderr, "Error while writing %s\n", argv[2] ) ;
        return -1 ;
    }
    
    image_free( img ) ;

    return 0 ;

}
