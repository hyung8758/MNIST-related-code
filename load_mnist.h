#ifndef LOAD_MNIST_H
#define LOAD_MNIST_H 

#define LABEL_MAGIC_NUMBER 0x00000801
#define IMAGE_MAGIC_NUMBER 0x00000803

#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>

/* perform necessary byte swap on little endian machines */

unsigned int endian_swap(unsigned int & bytes){
	bytes = ((bytes & 0x0000ffff) << 16) | ((bytes & 0xffff0000) >> 16); 
	return (bytes = ((bytes & 0x00ff00ff) << 8) | ((bytes & 0xff00ff00) >> 8)); 
}

/* code for loading sample images of each digit */

int load_mnist(const char * const img_fn, const char * const lbl_fn, unsigned int & width, unsigned int & height, std::vector<unsigned char**> mnist_digits[10], unsigned int limit = 0){
	bool img_diff_endian = false, lbl_diff_endian = false; 
	unsigned char label;
	unsigned char **current_img;
	unsigned int i, j, k, magic_number, img_n_sample, lbl_n_sample;
	std::fstream img_f(img_fn, std::ios_base::in | std::ios_base::binary), lbl_f(lbl_fn, std::ios_base::in | std::ios_base::binary);
	if (!img_f.is_open()){
		std::cerr<<"error opening '"<<img_fn<<"'\n";
		exit(-1);
	}
	if (!lbl_f.is_open()){
		std::cerr<<"error opening '"<<lbl_fn<<"'\n";
		exit(-1);
	}
	img_f.read((char *)&magic_number, 4);
	if (magic_number != IMAGE_MAGIC_NUMBER){
		if (endian_swap(magic_number) != IMAGE_MAGIC_NUMBER){
			std::cerr<<"error reading '"<<img_fn<<": invalid image file format'\n";
			exit(1);
		}
		img_diff_endian = true;
	}
	lbl_f.read((char *)&magic_number, 4);
	if (magic_number != LABEL_MAGIC_NUMBER){
		if (endian_swap(magic_number) != LABEL_MAGIC_NUMBER){
			std::cerr<<"error reading '"<<lbl_fn<<": invalid label file format'\n";
			exit(1);
		}
		lbl_diff_endian = true;
	}
	img_f.read((char *)&img_n_sample, 4);
	if (img_diff_endian){
		endian_swap(img_n_sample);
	}
	lbl_f.read((char *)&lbl_n_sample, 4);
	if (lbl_diff_endian){
		endian_swap(lbl_n_sample);
	}
	if (img_n_sample != lbl_n_sample){
		std::cerr<<"error: image file contains "<<img_n_sample<<"sample(s)"<<" and label file contains "<<lbl_n_sample<<"label(s), exiting\n";
		exit(1);
	}
	//std::cout<<img_n_sample<<std::endl;
	img_f.read((char *)&width, 4);
	img_f.read((char *)&height, 4);
	if (img_diff_endian){
		endian_swap(width);
		endian_swap(height);
	}
	//std::cout<<width<<", "<<height<<std::endl;
	for (i = 0; i < img_n_sample; ++i){
		lbl_f.read((char *)&label, 1);
		current_img = new unsigned char*[height]; 
		for (j = 0; j < height; ++j){
			current_img[j] = new unsigned char[width];
			for (k = 0; k < width; ++k){
				img_f.read((char *)(current_img[j] + k), 1);
			}
		}
		//std::cout<<(int)label<<std::endl;
		if (!limit || mnist_digits[(int)label].size() < limit){
			mnist_digits[(int)label].push_back(current_img);
		}
	}
	img_f.close();   //continue to read label file
	lbl_f.close();   //continue to read label file
	return 0;
}

/* code for loading sample images of each digit */

int load_mnist_for_pca(const char * const img_fn, const char * const lbl_fn, unsigned int & width, unsigned int & height, std::vector<double**> mnist_digits[10], unsigned int limit = 0){
	bool img_diff_endian = false, lbl_diff_endian = false; 
	unsigned char label;
	char cb;
	unsigned int i, j, k, magic_number, img_n_sample, N, lbl_n_sample;
	double **mean, **current_img;
	std::vector<double**>::iterator itr;
	std::fstream img_f(img_fn, std::ios_base::in | std::ios_base::binary), lbl_f(lbl_fn, std::ios_base::in | std::ios_base::binary);
	if (!img_f.is_open()){
		std::cerr<<"error opening '"<<img_fn<<"'\n";
		exit(-1);
	}
	if (!lbl_f.is_open()){
		std::cerr<<"error opening '"<<lbl_fn<<"'\n";
		exit(-1);
	}
	img_f.read((char *)&magic_number, 4);
	if (magic_number != IMAGE_MAGIC_NUMBER){
		if (endian_swap(magic_number) != IMAGE_MAGIC_NUMBER){
			std::cerr<<"error reading '"<<img_fn<<": invalid image file format'\n";
			exit(1);
		}
		img_diff_endian = true;
	}
	lbl_f.read((char *)&magic_number, 4);
	if (magic_number != LABEL_MAGIC_NUMBER){
		if (endian_swap(magic_number) != LABEL_MAGIC_NUMBER){
			std::cerr<<"error reading '"<<lbl_fn<<": invalid label file format'\n";
			exit(1);
		}
		lbl_diff_endian = true;
	}
	img_f.read((char *)&img_n_sample, 4);
	if (img_diff_endian){
		endian_swap(img_n_sample);
	}
	lbl_f.read((char *)&lbl_n_sample, 4);
	if (lbl_diff_endian){
		endian_swap(lbl_n_sample);
	}
	if (img_n_sample != lbl_n_sample){
		std::cerr<<"error: image file contains "<<img_n_sample<<"sample(s)"<<" and label file contains "<<lbl_n_sample<<"label(s), exiting\n";
		exit(1);
	}
	//std::cout<<img_n_sample<<std::endl;
	img_f.read((char *)&width, 4);
	img_f.read((char *)&height, 4);
	if (img_diff_endian){
		endian_swap(width);
		endian_swap(height);
	}
	//std::cout<<width<<", "<<height<<std::endl;
	N = 0;
	mean = new double*[height];
	for (i = 0; i < height; ++i){
		mean[i] = new double[width];
		for (j = 0; j < width; ++j){
			mean[i][j] = 0.0;
		}
	}
	for (k = 0; k < img_n_sample; ++k){
		lbl_f.read((char *)&label, 1);
		current_img = new double*[height]; 
		for (i = 0; i < height; ++i){
			current_img[i] = new double[width];
			for (j = 0; j < width; ++j){
				img_f.read(&cb, 1);
				current_img[i][j] = cb * 1.0;
			}
		}
		//std::cout<<(int)label<<std::endl;
		if (!limit || mnist_digits[(int)label].size() < limit){
			mnist_digits[(int)label].push_back(current_img);
			++N;
		}
	}
	for (k = 0; k < 10; ++k){
		for (itr = mnist_digits[k].begin(); itr != mnist_digits[k].end(); ++itr){
			for (i = 0; i < height; ++i){
				for (j = 0; j < width; ++j){
					mean[i][j] += (*itr)[i][j] * 1.0 / N;
				}
			}
		}
	}
	for (k = 0; k < 10; ++k){
		for (itr = mnist_digits[k].begin(); itr != mnist_digits[k].end(); ++itr){
			for (i = 0; i < height; ++i){
				for (j = 0; j < width; ++j){
					(*itr)[i][j] -= mean[i][j];
				}
			}
		}
	}
	for (i = 0; i < height; ++i){
		delete [] mean[i];
	}
	delete [] mean;
	img_f.close();
	lbl_f.close();
	return 0;
}

/* code for loading normalized images of each digit */

int load_normalized_mnist(const char * const img_fn, const char * const lbl_fn, unsigned int & width, unsigned int & height, std::vector<double**> mnist_digits[10], bool normalize_variance, unsigned int limit = 0){
	bool img_diff_endian = false, lbl_diff_endian = false; 
	unsigned char label, pixel;
	unsigned int i, j, k, magic_number, img_n_sample, lbl_n_sample, n_pixel;
	double e_x = 0, e_x2 = 0, s, v, **current_img;
	std::fstream img_f(img_fn, std::ios_base::in | std::ios_base::binary), lbl_f(lbl_fn, std::ios_base::in | std::ios_base::binary);
	if (!img_f.is_open()){
		std::cerr<<"error opening '"<<img_fn<<"'\n";
		exit(-1);
	}
	if (!lbl_f.is_open()){
		std::cerr<<"error opening '"<<lbl_fn<<"'\n";
		exit(-1);
	}
	img_f.read((char *)&magic_number, 4);
	if (magic_number != IMAGE_MAGIC_NUMBER){
		if (endian_swap(magic_number) != IMAGE_MAGIC_NUMBER){
			std::cerr<<"error reading '"<<img_fn<<": invalid image file format'\n";
			exit(1);
		}
		img_diff_endian = true;
	}
	lbl_f.read((char *)&magic_number, 4);
	if (magic_number != LABEL_MAGIC_NUMBER){
		if (endian_swap(magic_number) != LABEL_MAGIC_NUMBER){
			std::cerr<<"error reading '"<<lbl_fn<<": invalid label file format'\n";
			exit(1);
		}
		lbl_diff_endian = true;
	}
	img_f.read((char *)&img_n_sample, 4);
	if (img_diff_endian){
		endian_swap(img_n_sample);
	}
	lbl_f.read((char *)&lbl_n_sample, 4);
	if (lbl_diff_endian){
		endian_swap(lbl_n_sample);
	}
	if (img_n_sample != lbl_n_sample){
		std::cerr<<"error: image file contains "<<img_n_sample<<"sample(s)"<<" and label file contains "<<lbl_n_sample<<"label(s), exiting\n";
		exit(1);
	}
	//std::cout<<img_n_sample<<std::endl;
	img_f.read((char *)&width, 4);
	img_f.read((char *)&height, 4);
	if (img_diff_endian){
		endian_swap(width);
		endian_swap(height);
	}
	//std::cout<<width<<", "<<height<<std::endl;
	n_pixel = img_n_sample * width * height;
	for (i = 0; i < img_n_sample; ++i){
		lbl_f.read((char *)&label, 1);
		current_img = new double* [height]; 
		for (j = 0; j < height; ++j){
			current_img[j] = new double[width];
			for (k = 0; k < width; ++k){
				img_f.read((char *)&pixel, 1);
				current_img[j][k] = v = pixel * 1.0 / 255.0;
				e_x += v / n_pixel;
				e_x2 += v * v / n_pixel;
			}
		}
		//std::cout<<(int)label<<std::endl;
		if (!limit || mnist_digits[(int)label].size() < limit){
			mnist_digits[(int)label].push_back(current_img);
		}
	}
	s = sqrt(e_x2 - e_x * e_x);
	if (normalize_variance){
		for (k = 0; k < 10; ++k){
			for (std::vector<double**>::iterator itr = mnist_digits[k].begin(); itr != mnist_digits[k].end(); ++itr){
				for (i = 0; i < height; ++i){
					for (j = 0; j < width; ++j){
						(*itr)[i][j] -= e_x;
						(*itr)[i][j] /= s;
					}
				}
			}
		}
	}else{
		for (k = 0; k < 10; ++k){
			for (std::vector<double**>::iterator itr = mnist_digits[k].begin(); itr != mnist_digits[k].end(); ++itr){
				for (i = 0; i < height; ++i){
					for (j = 0; j < width; ++j){
						(*itr)[i][j] -= e_x;
					}
				}
			}
		}
	}
	img_f.close();   //continue to read label file
	lbl_f.close();   //continue to read label file
	return 0;
}

/* code for freeing all images in memory (tested with valgrind memcheck) */

template <typename T>
void free_mnist(const unsigned int height, const std::vector<T**> mnist_digits[]){
	unsigned int i, j, k;
	for (i = 0; i < 10; ++i){
		for (j = 0; j < mnist_digits[i].size(); ++j){
			for (k = 0; k < height; ++k){
				delete [] mnist_digits[i][j][k];
			}
			delete [] mnist_digits[i][j];
		}
	}
}

template <typename T>
void free_mnist(const unsigned int height, const std::vector<T**> & mnist_digits){
	unsigned int i, j;
	for (i = 0; i < mnist_digits.size(); ++i){
		for (j = 0; j < height; ++j){
			delete [] mnist_digits[i][j];
		}
		delete [] mnist_digits[i];
	}
}

/* code for showing an approximate image of a digit */ 

void display_mnist_digit(const unsigned int width, const unsigned int height, unsigned char ** const mnist_digit){
	for (unsigned int i = 0; i < height; ++i){
		for (unsigned int j = 0; j < width; ++j){
			std::cout<<(mnist_digit[i][j] >= 128 ? "#" : ".")<<",";	
		}
		std::cout<<"\n";
	}
	std::cout<<"\n";
}

#endif
