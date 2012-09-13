#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#define DEFAULT_ALPHA .01

#include <time.h>
#include <stdlib.h>
#include <vector>
#include <iostream>

void rand_permute(int, int[]);

/* code for learning a perceptron, specialized for 2-dimensional data that are grouped into 2 classes */

template <typename T>
double *perceptron(unsigned int width, unsigned int height, std::vector<T**> P, std::vector<T**> const N, unsigned int max_itr, double rtol, double alpha = DEFAULT_ALPHA){
	unsigned int i, j, k, ci, p = P.size(), s = p + N.size(), m = width * height, *p_arr = new int[s];
	double d, f, err = 1.0, *w = new double[m + 1];
	for (i = 0; i <= m; ++i){
		w[i] = 0.0;
	}
	while (err >= rtol){
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
			err += (d = f - (p_arr[i] >= p ? -1 : 1));
			if (p_arr[i] >= p){
				for (j = 0; j < height; ++j){
					for (k = 0; k < width; ++k){
						ci = j * width + k;
						w[ci] -= alpha * d * N[p_arr[i] - p][j][k];
					}
				}
			}else{
				for (j = 0; j < height; ++j){
					for (k = 0; k < width; ++k){
						ci = j * width + k;
						w[ci] -= alpha * d * P[p_arr[i]][j][k];
					}
				}
			}
			w[m] = alpha * d;
		}
		err /= s;
		std::cout<<err<<"\n";
	}
	delete [] p_arr;
	return w;
}

void rand_permute(int m, int a[]){
	int i, j;
	srand (time(0));
	for (i = 0; i < m; ++i){
		j = rand() % (i + 1);
		a[i] = j;
		a[j] = i;
	}
}

#endif
