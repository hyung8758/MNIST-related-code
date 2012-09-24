#ifndef MISC_H
#define MISC_H

#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <math.h>
#include <gsl/gsl_math.h>

std::string partition_str(const unsigned int pt[]){
	unsigned int i;
	std::string ret = "{";
	for (i = 1; i < pt[0]; ++i){
		ret += pt[i] + '0';
		ret += ", ";
	}
	ret += pt[i] + '0';
	ret += "}";
	return ret;
}

void rand_permute(unsigned int m, unsigned int a[]){
	unsigned int i, j;
	srand (time(0));
	a[0] = 0;
	for (i = 1; i < m; ++i){
		if ( (j = rand() % (i + 1)) != i ){
			a[i] = a[j];
			a[j] = i;
		}else{
			a[i] = i;
		}
	}
}

template <typename T>
double dist2(unsigned int width, unsigned int height, T ** const a, T ** const b){
	double d, sum = 0;
	unsigned int i, j;
	for (i = 0; i < height; ++i){
		for (j = 0; j < width; ++j){
			d = b[i][j] - a[i][j]; 
			sum += d * d; 
		}
	}
	return sum;
}

template <typename T>
double l2(unsigned int width, unsigned int height, T ** const a){
	double sum = 0;
	unsigned int i, j;
	for (i = 0; i < height; ++i){
		for (j = 0; j < width; ++j){
			sum += a[i][j] * a[i][j]; 
		}
	}
	return sum;
}

void normalize(unsigned int width, unsigned int height, double ** v){
	unsigned int i, j;
	double l = sqrt(l2<double>(width, height, v));
	for (i = 0; i < height; ++i){
		for (j = 0; j < width; ++j){
			v[i][j] /= l; 
		}
	}
}

template <typename T>
void pixelize(unsigned int width, unsigned int height, T ** const v, unsigned char ** p){
	unsigned int i, j, m = width * height;
	T min = v[0][0], max = v[0][0], c, r;
	for (i = 1; i < m; ++i){
		c = v[i / width][i % width];
		if (c > max){
			max = c;
		}else if (c < min){
			min = c;
		}
	}
	r = max - min;
	for (i = 0; i < height; ++i){
		for (j = 0; j < width; ++j){
			p[i][j] = (unsigned char)((v[i][j] - min) / r * 255.0);
		}
	}
}

#endif
