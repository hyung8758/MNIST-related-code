#ifndef LIN_ALG_H
#define LIN_ALG_H

#include <assert.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_permutation.h>
#include <gsl/gsl_linalg.h>

int invert_matrix(const gsl_matrix *A, gsl_matrix & Ai){
	int signum;
	assert(A -> size1 == A -> size2 && Ai.size1 == Ai.size2 && A -> size1 == Ai.size1);
	gsl_permutation *P = gsl_permutation_alloc(A->size1);
	gsl_matrix *_A = gsl_matrix_alloc(A->size1, A->size2);
	gsl_matrix_memcpy(_A, A);
	gsl_linalg_LU_decomp(_A, P, &signum);
	gsl_linalg_LU_invert(_A, P, &Ai);
	gsl_permutation_free(P);
	gsl_matrix_free(_A);
	return 0;
}

gsl_matrix *invert_matrix(const gsl_matrix *A){
	int signum;
	assert(A -> size1 == A -> size2);
	gsl_permutation *P = gsl_permutation_alloc(A->size1);
	gsl_matrix *_A = gsl_matrix_alloc(A->size1, A->size2);
	gsl_matrix *Ai = gsl_matrix_alloc(A->size1, A->size2);
	gsl_matrix_memcpy(_A, A);
	gsl_linalg_LU_decomp(_A, P, &signum);
	gsl_linalg_LU_invert(_A, P, Ai);
	gsl_permutation_free(P);
	gsl_matrix_free(_A);
	return Ai;
}

#endif
