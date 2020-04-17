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

	image_save_ppm( image, "image.ppm" );
	
	image_t * cat_image = NULL;
	if(image_cat_ver(&cat_image, image, image)){
		fprintf(stderr, "Error concatenating images\n");
		return -1;
	}
	image_save_ppm( cat_image, "cat_image.ppm" );
	
	image_t * crop_image = NULL;
		
	if(image_crop_rows(&crop_image, image, 22, 420)){
		fprintf(stderr, "Error cropping image\n");
		return -1;
	}
	image_save_ppm(crop_image, "crop_image.ppm");

	image_free(image);
	image_free(cat_image);
	free(crop_image);
	fclose(fp);

	return 0;
}
