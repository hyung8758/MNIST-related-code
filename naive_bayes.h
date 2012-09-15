#ifndef NAIVE_BAYES_H
#define NAIVE_BAYES_H

#define NC 0.39894
#define EPS 1e-10
#define INF 1e37

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
		const unsigned int width, height, N;    //N: number of catagor(ies)
		const std::vector<T**> *C;
		double ***m, ***s2;
	public:
		naive_bayes(const unsigned int _width, const unsigned int _height, const unsigned int _N, const std::vector<T**> _C[]) : width(_width), height(_height), N(_N), C(_C), m(new double**[_N]), s2(new double**[_N]){
			unsigned int i, j, k, l, n;
			double e_x, e_x2;
			for (k = 0; k < N; ++k){
				m[k] = new double*[height];
				s2[k] = new double*[height];
				n = C[k].size();
				for (i = 0; i < height; ++i){
					m[k][i] = new double[width];
					s2[k][i] = new double[width];
					for (j = 0; j < width; ++j){
						e_x = 0;
						e_x2 = 0;
						for (l = 0; l < n; ++l){
							e_x += C[k][l][i][j] * 1.0 / n;
							e_x2 += C[k][l][i][j] * C[k][l][i][j] * 1.0 / n;
						}
						m[k][i][j] = e_x;
						s2[k][i][j] = e_x2 - e_x * e_x;
					}
				}
			}
		} 

		~naive_bayes(void){
			unsigned int i, k;
			for (k = 0; k < N; ++k){
				for (i = 0; i < height; ++i){
					delete [] m[k][i];
					delete [] s2[k][i];
				}
				delete [] m[k];
				delete [] s2[k];
			}
			delete [] m;
			delete [] s2;
		} 

		unsigned int mlc(T ** const F) const{   //note: assuming each feature has a Gaussian distribution and using Gaussian function to estimate p(F|C), return the most likely catagory of F
			unsigned int i, j, k, m_k = 0;
			double d, s, lp, max_lp = -INF;
			for (k = 0; k < N; ++k){
				lp = 0.0;
				for (i = 0; i < height; ++i){
					for (j = 0; j < width; ++j){
						s = sqrt(s2[k][i][j]);
						if (s != 0){
							d = (F[i][j] - m[k][i][j]) / s;
							lp += -.5 * d * d - log(s);
						}else{
							d = F[i][j] - m[k][i][j];
							if (d > EPS || d < -EPS){
								lp = -INF;
								break;
							}
						}
					}
					if (lp == -INF){
						break;
					}
				}
				//std::cout<<"lp == "<<lp<<"\n";
				if (lp > max_lp){
					max_lp = lp;
					m_k = k;
				}
			}
			return m_k;
		}
};

#endif
