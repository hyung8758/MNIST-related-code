#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#define DEFAULT_ALPHA .000001

#include <time.h>
#include <stdlib.h>
#include <vector>
#include <iostream>

void rand_permute(unsigned int, unsigned int[]);

/* code for learning a perceptron, specialized for 2-dimensional data that are grouped into 2 classes */

template <typename T>
double *perceptron(unsigned int width, unsigned int height, std::vector<T**> P, std::vector<T**> N, unsigned int max_itr, double rtol, double alpha = DEFAULT_ALPHA){
	unsigned int i, j, k, ci, itr = 0, p = P.size(), s = p + N.size(), m = width * height, *p_arr = new unsigned int[s];
	double d, f, err = 1.0, *w = new double[m + 1];
	for (i = 0; i <= m; ++i){
		w[i] = 0.0;
	}
	while (itr++ <= max_itr && err >= rtol){
		err = 0.0;
		rand_permute(s, p_arr);
		for (i = 0; i <= m; ++i){
			f = 0.0;
			if (p_arr[i] >= p){   //the inner-product term
				for (j = 0; j < height; ++j){
					for (k = 0; k < width; ++k){ 
						ci = j * width + k;
						f += w[ci] * N[p_arr[i] - p][j][k];
					}
				}
			}else{
				for (j = 0; j < height; ++j){
					for (k = 0; k < width; ++k){ 
						ci = j * width + k;
						f += w[ci] * P[p_arr[i]][j][k];
					}
				}
			}
			f += w[m];   //plus the bias term 
			if (p_arr[i] >= p){
				d = f + 1;
				if (f >= 0){
					err += 1.0 / s;
				}
				for (j = 0; j < height; ++j){
					for (k = 0; k < width; ++k){
						ci = j * width + k;
						w[ci] -= alpha * d * N[p_arr[i] - p][j][k];
					}
				}
			}else{
				d = f - 1;
				if (f < 0){
					err += 1.0 / s;
				}
				for (j = 0; j < height; ++j){
					for (k = 0; k < width; ++k){
						ci = j * width + k;
						w[ci] -= alpha * d * P[p_arr[i]][j][k];
					}
				}
			}
			w[m] -= alpha * d;
		}
		std::cout<<"error rate after iteration "<<itr<<": "<<err<<"\n";
	}
	delete [] p_arr;
	return w;
}

void rand_permute(unsigned int m, unsigned int a[]){
	unsigned int i, j;
	srand (time(0));
	for (i = 0; i < m; ++i){
		j = rand() % (i + 1);
		a[i] = a[j];
		a[j] = i;
	}
}

#endif
