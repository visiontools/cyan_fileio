#include <stdio.h>
#include <cyan/cyan.h>
#include <cyan/fileio/imageio.h>

int main(int argc, char** argv) {

    image_t* img = NULL ;
    
    if ( argc != 4  ) {
        fprintf( stderr, "usage: %s <input_image_file> <type> <output_image_file>\n", argv[0] ) ;
        fprintf( stderr, "\n") ;
        fprintf( stderr, "For available types, you can use:\n");
        fprintf( stderr, "\t identify -list format \n");
        fprintf( stderr, "\n") ;
        fprintf( stderr, "\t For example: %s ./lena.png PNG ./output.png\n", argv[0]) ;
        return -1 ;
    }


    if( image_import( &img, argv[1] ) != ERR_OK ) {
        fprintf( stderr, "Error while opening %s\n", argv[1] ) ;
        return -1 ;
    }

    if (image_export( img, argv[3], argv[2] ) != ERR_OK ) {
        fprintf( stderr, "Error while writing %s\n", argv[3] ) ;
        return -1 ;
    }
    
    image_free( img ) ;

    return 0 ;

}
