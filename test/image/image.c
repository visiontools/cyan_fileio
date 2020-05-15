#include <stdio.h>
#include <cyan/cyan.h>
#include <cyan/fileio/imageio.h>

int main(int argc, char** argv) {

    image_t* img ;
    img = NULL ;

    image_import( &img, "./lena.png" ) ; 


    image_free( img ) ;

    return 0 ;

}
