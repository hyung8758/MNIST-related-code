#ifndef MNIST_VIZ_H
#define MNIST_VIZ_H

#include "png_util.h"

/* code for saving image as png format (for visualization purposes) */

void mnist_digit_2_png(const unsigned int width, const unsigned int height, unsigned char ** const mnist_digit, const char * const filename){
	unsigned int i, j;
	png_bytep *p = new png_bytep[height];
	for (i = 0; i < height; ++i){
		p[i] = new png_byte[width];
		for (j = 0; j < width; ++j){
			p[i][j] = 255 - mnist_digit[i][j];
		}
	}
	write_png_file(width, height, filename, p);
	for (i = 0; i < height; ++i){
		delete [] p[i];
	}
	delete [] p;
}

#endif
