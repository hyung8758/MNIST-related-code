#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#define DEFAULT_ALPHA .0000000001

#include <vector>
#include <iostream>
#include "misc.h"

/* code for learning a perceptron, specialized for 2-dimensional data that are grouped into 2 classes */

template <typename T>
double *perceptron(const unsigned int width, const unsigned int height, const std::vector<T**> S[], const unsigned int P[], const unsigned int N[], const unsigned int max_itr, const double rtol, const double alpha = DEFAULT_ALPHA, const bool verbose = true){
	unsigned int i, j, k, c, b_i, itr = 0, s = 0, s_p = P[0], s_n = N[0], m = width * height, p, *e_arr = new unsigned int[s_p + s_n], *p_arr;
	double d, f, err = 1.0, *w = new double[m + 1];
	if (verbose){
		std::cout<<"\nseparating "<<partition_str(P)<<" and "<<partition_str(N)<<":\n\n";
	}
	for (i = 0; i < s_p; ++i){
		e_arr[i] = (s += S[P[i + 1]].size()); 
	}
	p = s;
	for (i = 0; i < s_n; ++i){
		e_arr[s_p + i] = (s += S[N[i + 1]].size());
	}
	for (i = 0; i <= m; ++i){
		w[i] = 0.0;
	}
	p_arr = new unsigned int[s];
	while (itr++ < max_itr && err >= rtol){
		err = 0.0;
		rand_permute(s, p_arr);
		for (i = 0; i < s; ++i){
			f = w[m];   //plus the bias term 
			c = 0;
			if (p_arr[i] >= p){   //the inner-product term
				b_i = p;
				while (e_arr[c + s_p] <= p_arr[i]){
					b_i += S[N[++c]].size();  //note: value of c is off by 1
				}
				for (j = 0; j < height; ++j){
					for (k = 0; k < width; ++k){ 
						f += w[j * width + k] * S[N[c + 1]][p_arr[i] - b_i][j][k];
					}
				}
				d = f + 1;
				if (f >= 0){
					err += 1.0 / s;
				}
				for (j = 0; j < height; ++j){
					for (k = 0; k < width; ++k){
						w[j * width + k] -= alpha * d * S[N[c + 1]][p_arr[i] - b_i][j][k];
					}
				}
			}else{
				b_i = 0;
				while (e_arr[c] <= p_arr[i]){
					b_i += S[P[++c]].size();   //note: value of c is off by 1
				}
				for (j = 0; j < height; ++j){
					for (k = 0; k < width; ++k){ 
						f += w[j * width + k] * S[P[c + 1]][p_arr[i] - b_i][j][k];
					}
				}
				d = f - 1;
				if (f < 0){
					err += 1.0 / s;
				}
				for (j = 0; j < height; ++j){
					for (k = 0; k < width; ++k){
						w[j * width + k] -= alpha * d * S[P[c + 1]][p_arr[i] - b_i][j][k];
					}
				}
			}
			w[m] -= alpha * d;
		}
		if (verbose){
			std::cout<<"error rate after iteration "<<itr<<": "<<err<<"\n";
		}
	}
	delete [] p_arr;
	delete [] e_arr;
	return w;
}

template <typename T>
bool f(const unsigned int width, const unsigned int height, const double *w, T ** const img){
	double y = 0.0;
	for (unsigned int i = 0; i < height; ++i){
		for (unsigned int j = 0; j < width; ++j, ++w){
			y += *w * img[i][j];
		}
	}
	y += *w;
	return y >= 0;
}

#endif
