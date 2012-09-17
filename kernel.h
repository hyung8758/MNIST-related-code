#ifndef KERNEL_H
#define KERNEL_H

#include <math.h>

template <typename T>
double inner_prod(const unsigned int width, const unsigned int height, T ** const u, T ** const v){
	unsigned int i, j;
	double sum = 0;
	for (i = 0; i < height; ++i){
		for (j = 0; j < width; ++j){
			sum += u[i][j] * v[i][j];
		}
	}
	return sum;
}

template <typename T>
double p_d(const unsigned int width, const unsigned int height, const double p, T ** const u, T ** const v){
	return pow(inner_prod<T>(width, height, u, v), p);
}

template <typename T>
double th(const unsigned int width, const unsigned int height, const double a, const double b, T ** const u, T ** const v){
	return tanh(a * inner_prod<T>(width, height, u, v) + b);
}

template <typename T>
double sigmoid(const unsigned int width, const unsigned int height, const double a, const double b, T ** const u, T ** const v){
	return 1.0 / (1.0 + exp(a * inner_prod<T>(width, height, u, v) + b));
}

template <typename T>
double rad(const unsigned int width, const unsigned int height, const double s, T ** const u, T ** const v){
	unsigned int i, j;
	double d, sum = 0;
	for (i = 0; i < height; ++i){
		for (j = 0; j < width; ++j){
			d = u[i][j] - v[i][j];
			sum += d * d;
		}
	}
	return exp(-sum / 2.0 / (s * s));
}

#endif
