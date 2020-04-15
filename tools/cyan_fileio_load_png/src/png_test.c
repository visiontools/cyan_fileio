#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <cyan/image/image.h>

#include <cyan_fileio/load_png.h>
#include <cyan_fileio/save_ppm.h>

int main(int argc, char** argv, char * envv){

	if(argc != 2){
		fprintf(stderr, "Usage : %s file.png\n", argv[0] );
		return -1;
	}
	
	FILE * fp = NULL;
	fp = fopen(argv[1], "r");
	if(fp == NULL){
		fprintf(stderr, "Couldn't open file. \n Error : %d, (%s)\n", errno, strerror(errno));
		return -1;
	}

	image_t * image = NULL;
	image = png2image(fp);
	if(image == NULL){
		fprintf(stderr, "Image allocation failed\n");
		return -1;
	}

	image_t * cat_image = NULL;
	image_cat_hor(&cat_image, image, image);
	if(cat_image == NULL){
		fprintf(stderr, "cat_image is NULL\n");
		return -1;
	}
	image_save_ppm( image, "image.ppm" );
	image_save_ppm( cat_image, "cat_image.ppm" );
	image_free(image);
	fclose(fp);

	return 0;
}
