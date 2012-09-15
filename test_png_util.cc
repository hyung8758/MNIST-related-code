#include "png_util.h"

int main(int argc, char *argv[]){
	unsigned int i, j, width = 128, height = 128;
	png_bytep *p = new png_bytep[height];
	for (i = 0; i < height; ++i){
		p[i] = new png_byte[width * 4]; 
		for (j = 0; j < width; ++j){
			p[i][j * 4] = p[i][j * 4 + 1] = p[i][j * 4 + 2] = (i * i + j * j) / 256; 
			p[i][j * 4 + 3] = 0;
		}
	}
	write_png_file(width, height, "png_test_result.png", p);
	for (i = 0; i < height; ++i){
		delete [] p[i];
	}
	delete [] p;
	return 0;
}
