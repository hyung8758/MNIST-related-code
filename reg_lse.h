#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#define DEFAULT_LAMBDA .1    //the regularization coefficient for the |w|^2 term
#define G_RAD 1.0

#include <vector>
#include <iostream>
#include "misc.h"
#include "lin_alg.h"
#include "kernel.h"    //can choose any function from "kernel.h" as kernel function

/* code for computing decision boundary with the regularized least square rule and some feature-mapping function */

template <typename T>
class reg_lse{
	private:
		unsigned int width, height, n, np, nn;
		double lambda, *w;
		std::vector<T**> X;
	public:
		reg_lse(const unsigned int _width, const unsigned int _height, const std::vector<T**> S[], const unsigned int P[], const unsigned int N[], const double _lambda = DEFAULT_LAMBDA) : width(_width), height(_height), lambda(_lambda){
			unsigned int i, j, s_p = P[0], s_n = N[0];
			double v;
			gsl_matrix *K, *Ki; 
			typename std::vector<T**>::const_iterator itr;
			np = 0;
			nn = 0;
			for (i = 1; i <= s_p; ++i){
				np += (S[P[i]]).size();
				for (itr = (S[P[i]]).begin(); itr != (S[P[i]]).end(); ++itr){
					X.push_back(*itr);	
				}
			}
			for (i = 1; i <= s_n; ++i){
				nn += (S[N[i]]).size();
				for (itr = (S[N[i]]).begin(); itr != (S[N[i]]).end(); ++itr){
					X.push_back(*itr);	
				}
			}
			n = np + nn;
			w = new double[n];
			K = gsl_matrix_alloc(n, n);
			for (i = 0; i < n; ++i){
				gsl_matrix_set(K, i, i, rad<T>(width, height, G_RAD, X[i], X[i]) + lambda);
				for (j = i + 1; j < n; ++j){
					v = rad<T>(width, height, G_RAD, X[i], X[j]);    //note: can choose any kernel function here 
					gsl_matrix_set(K, i, j, v);
					gsl_matrix_set(K, j, i, v);
				}
			}
			Ki = invert_matrix(K);
			for (i = 0; i < n; ++i){
				w[i] = 0.0;
				for (j = 0; j < np; ++j){
					w[i] += gsl_matrix_get(Ki, i, j);
				}
				for (j = np; j < n; ++j){
					w[i] -= gsl_matrix_get(Ki, i, j);
				}
			}
			gsl_matrix_free(K);
			gsl_matrix_free(Ki);
		}

		bool f(T ** const x) const{
			unsigned int i;
			double y = 0.0;
			for (i = 0; i < n; ++i){
				y += rad<T>(width, height, G_RAD, x, X[i]) * w[i];
			}
			return y >= 0.0;
		}

		~reg_lse(void){
			delete [] w;
		}

};

#endif
