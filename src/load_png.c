#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <errno.h>

#include <png.h>

#include <cyan/image/image.h>
#include <cyan/color/color.h>

#include <cyan_fileio/load_png.h>

image_t* png2image(FILE * fp) {
	
	image_t * image;

	if(!fp){
		fprintf(stderr, "Empty file pointer in png2image().\n");
		return NULL;
	}
    png_structp	png_ptr;
    png_infop info_ptr;
    png_uint_32 width;
    png_uint_32 height;
    int bit_depth;
    int color_type;
    int interlace_method;
    int compression_method;
    int filter_method;
    int i,j;
    png_bytepp rows;

    png_ptr = png_create_read_struct (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (! png_ptr) {
	return NULL;
    }
    info_ptr = png_create_info_struct (png_ptr);
    if (! png_ptr) {
	return NULL;
    }

    //TODO : check what happens if a non .png file is given
    //There exists a function to check if the file is a real .png

    png_init_io (png_ptr, fp);
    png_read_png (png_ptr, info_ptr, 0, 0);
    png_get_IHDR (png_ptr, info_ptr, & width, & height, & bit_depth,
		  & color_type, & interlace_method, & compression_method,
		  & filter_method);
		if(interlace_method != 0){
		fprintf(stderr, "Behaviour could be unexpected in the following");
		//TODO See why ? Fix ? Who doesn't like a surprise ?
	}

    //Uncomment the following line if you want to ignore the alpha channel (never tested)
    //   png_set_strip_alpha(png_ptr);	
    image = image_new(width, height);
	if(!image){
		fprintf(stderr, "The image couldn't be created\n");
		return NULL;
	}	
    rows = png_get_rows (png_ptr, info_ptr);
    printf ("Width is %d, height is %d\n", width, height);
    
    int rowbytes;
    rowbytes = png_get_rowbytes (png_ptr, info_ptr);
    printf ("Row bytes = %d\n", rowbytes);
    
	double R,G,B;
	int temp[3];
	//Remark, I have no idea which flags shall be used in cyan
	//It might not be the same as the one define in the png library
	if(color_type == PNG_COLOR_TYPE_RGB){
		image->monochrome = 0;
 		for (i = 0; i < height; i++) {
			for (j = 0; j < width ; j++) {
				
				int coord;
				coord = j + i*image->cols ;
		
				R = rows[i][3*j]/(double) 255 ;
				G = rows[i][3*j+1]/(double) 255 ;
				B = rows[i][3*j+2]/ (double) 255 ;
				
				RGB_to_XYZ( color_type, R, G, B, &(image->X[coord]), &(image->Y[coord]), &(image->Z[coord]));
				
			}  
	       }
	}else{
		image->monochrome = 1;
		 for (i = 0; i < height; i++) {
			for (j = 0; j < width ; j++) {
				
				int coord;
				coord = j + i*image->cols ;
		
				R = rows[i][j]/(double) 255 ;
				
				RGB_to_XYZ( color_type, R, R, R, &(image->X[coord]), &(image->Y[coord]), &(image->Z[coord]));
				
			}  
	       }
	}

	png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);	
    
	return image;

}

