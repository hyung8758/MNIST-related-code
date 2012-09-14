#ifndef NAIVE_BAYES_H
#define NAIVE_BAYES_H

#include <vector>
#include <math.h>
 
/*
 * naive bayes classifier with uniform prior (i.e. assuming p(c) is identical for all c in C)
 *
 * note: probably will not perform well on MNIST dataset due to high dimensionality
 *
 */


template <typename T>
class naive_bayes{
	private:
		const unsigned int width, height, N; 
		const std::vector<T**> C[];
		const double ***m, ***s;
	public:
		naive_bayes(const unsigned int _width, const unsigned int _height, const unsigned int _N, const std::vector<T**> _C[]) : width(_width), height(_height), N(_N), C(_C), s(new const double**[_N]), m(new const double**[_N]) {
			unsigned int i, j, k, l, n;
			double e_x, e_x2;
			for (k = 0; k < N; ++k){
				s[k] = new const double*[height];
				n = C[k].size();
				for (i = 0; i < height; ++i){
					s[k][i] = new double[width];
					for (j = 0; j < width; ++j){
						e_x = 0;
						e_x2 = 0;
						for (l = 0; l < n; ++l){
							e_x += C[l][i][j] * 1.0 / n;
							e_x2 += C[l][i][j] * C[l][i][j] * 1.0 / n;
						}
						m[k][i][j] = e_x;
						s[k][i][j] = sqrt(e_x2 - e_x);
					}
				}
			}
		} 
		~naive_bayes(void){
			unsigned int i, k;
			for (k = 0; k < N; ++k){
				for (i = 0; i < height; ++i){
					delete [] m[k][i];
					delete [] s[k][i];
				}
				delete [] m[k];
				delete [] s[k];
			}
			delete [] m;
			delete [] s;
		}
		double pF_cond_C(unsigned int width, unsigned int height, T ** const F, const std::vector<T**> C) const{   //note: assuming each feature has a Gaussian distribution and using Gaussian function to estimate p(F|C)
			return 0;
		}
};

#endif
