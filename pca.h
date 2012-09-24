#ifndef PCA_H
#define PCA_H

#include <vector>
#include <iostream>
#include <assert.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_eigen.h>
#include "misc.h"

template <typename T>
class pca{
	private:
		unsigned int width, height, N;
		double *eval, ***pc;
	public:
		pca(const unsigned int _width, const unsigned int _height, const unsigned int _N, const std::vector<T**> S) : width(_width), height(_height), N(_N), eval(new double[N]), pc(new double**[N]) {
			unsigned int i, j, k, l, nS = S.size(), m = width * height;
			double **cov;
			typename std::vector<T**>::const_iterator itr;
			for (i = 0; i < N; ++i){
				pc[i] = new double*[height];
				for (j = 0; j < height; ++j){
					pc[i][j] = new double[width];
				}
			}
			cov = new double*[m];
			for (i = 0; i < m; ++i){
				cov[i] = new double[m];
				for (j = 0; j < m; ++j){
					cov[i][j] = 0.0;
				}
			}
			for (itr = S.begin(); itr != S.end(); ++itr){
				for (i = 0, k = 0; i < height; ++i){
					for (j = 0; j < width; ++j, ++k){
						for (l = 0; l <= k; ++l){
							cov[k][l] += (*itr)[l / width][l % width] * (*itr)[i][j] * 1.0 / nS;
						}
					}
				}
			}   //note: assuming means are all 0
			gsl_matrix *cov_m = gsl_matrix_alloc(m, m);
			for (k = 0; k < m; ++k){
				for (l = 0; l < k; ++l){
					gsl_matrix_set(cov_m, k, l, cov[k][l]);
					gsl_matrix_set(cov_m, l, k, cov[k][l]);
				}
				gsl_matrix_set(cov_m, k, k, cov[k][k]);
			}
			gsl_vector *eval = gsl_vector_alloc(m);
			gsl_matrix *evec = gsl_matrix_alloc(m, m);
			gsl_eigen_symmv_workspace *wsp = gsl_eigen_symmv_alloc (m);
			gsl_eigen_symmv (cov_m, eval, evec, wsp);
			gsl_eigen_symmv_free (wsp);
			gsl_eigen_symmv_sort (eval, evec, GSL_EIGEN_SORT_ABS_DESC);
			for (i = 0; i < N; i++){  //double eval_i = gsl_vector_get (eval, i);
				for (j = 0; j < m; ++j){
					pc[i][j / width][j % width] = gsl_vector_get(&gsl_matrix_column(evec, i).vector, j);
				}
				normalize(width, height, pc[i]);
			}
			gsl_vector_free (eval);
			gsl_matrix_free (evec);
			gsl_matrix_free (cov_m);
			for (i = 0; i < m; ++i){
				delete [] cov[i];
			}
			delete [] cov;
		}

		~pca(void){
			unsigned int i, j;
			delete [] eval;
			for (i = 0; i < N; ++i){
				for (j = 0; j < height; ++j){
					delete [] pc[i][j];
				}
				delete [] pc[i];
			}
			delete [] pc;
		}

		double ** const get_pc(unsigned int n) const{
			assert(n < N);
			return pc[n];
		}

		double * proj(T ** const v) const{
			unsigned int i, j, k;
			double *p = new double[N];
			for (k = 0; k < N; ++k){
				p[k] = 0.0;
				for (i = 0; i < height; ++i){
					for (j = 0; j < width; ++j){
						p[k] += v[i][j] * pc[k][i][j];
					}
				}
			}
			return p;
		}

		void print_pc(void) const{
			unsigned int i, j, k; 
			for (k = 0; k < N; ++k){
				std::cout<<"eigenvalue:\n"<<eval[k]<<"\neigenvector:\n";
				for (i = 0; i < height; ++i){
					for (j = 0; j < width; ++j){
						std::cout<<pc[k][i][j]<<", ";
					}
					std::cout<<"\n";
				}
				std::cout<<"\n";
			}
		}
};

#endif
