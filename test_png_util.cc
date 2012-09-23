#include "png_util.h"

int main(int argc, char *argv[]){
	unsigned int i, j, width = 128, height = 128;
	png_bytep *p = new png_bytep[height];
	for (i = 0; i < height; ++i){
		p[i] = new png_byte[width]; 
		for (j = 0; j < width; ++j){
			p[i][j] = (i * i + j * j) / 256; 
		}
	}
	write_png_file(width, height, "png_test_result.png", p);
	for (i = 0; i < height; ++i){
		delete [] p[i];
	}
	delete [] p;
	return 0;
}
