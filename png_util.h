#ifndef PNG_UTIL_H
#define PNG_UTIL_H

#define BIT_DEPTH 16
#define COLOR_TYPE 4

#include <assert.h>
#include <png.h>

void write_png_file(const unsigned int width, const unsigned int height, const char * const output_fn, png_bytep * const output_pixel){
	FILE *fp = fopen(output_fn, "wb");
	assert(fp);
	png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	assert(png_ptr);
	png_infop info_ptr = png_create_info_struct(png_ptr);
	assert(info_ptr);
	assert(!setjmp(png_jmpbuf(png_ptr)));
	png_init_io(png_ptr, fp);
	assert(!setjmp(png_jmpbuf(png_ptr)));
	png_set_IHDR(png_ptr, info_ptr, width, height, BIT_DEPTH, COLOR_TYPE, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
	png_write_info(png_ptr, info_ptr);
	assert(!setjmp(png_jmpbuf(png_ptr)));
	png_write_image(png_ptr, output_pixel);
	assert(!setjmp(png_jmpbuf(png_ptr)));
	png_write_end(png_ptr, NULL);
	fclose(fp);
}

#endif
