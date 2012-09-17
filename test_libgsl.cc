#include <iostream>
#include <gsl/gsl_math.h>
#include <gsl/gsl_eigen.h>
#include "lin_alg.h"

int main (void){
	int i;
	double data[] = {1.0, 1.0/2.0, 1.0/3.0, 1.0/4.0, 1.0/2.0, 1.0/3.0, 1.0/4.0, 1.0/5.0, 1.0/3.0, 1.0/4.0, 1.0/5.0, 1.0/6.0, 1.0/4.0, 1.0/5.0, 1.0/6.0, 1.0/7.0};
	gsl_matrix *m_data = gsl_matrix_alloc(4, 4);
	for (i = 0; i < 16; ++i){
		std::cout<<data[i]<<std::endl;
		gsl_matrix_set(m_data, i / 4, i % 4, data[i]);
	}
	gsl_matrix_view m = gsl_matrix_view_array(data, 4, 4);  //note: this line modifies the data array!! 
	gsl_vector *eval = gsl_vector_alloc(4);
	gsl_matrix *evec = gsl_matrix_alloc(4, 4);
	gsl_eigen_symmv_workspace *w = gsl_eigen_symmv_alloc (4);
	gsl_eigen_symmv (&m.matrix, eval, evec, w);
	gsl_eigen_symmv_free (w);
	gsl_eigen_symmv_sort (eval, evec, GSL_EIGEN_SORT_ABS_ASC);
	for (i = 0; i < 4; i++){
		double eval_i = gsl_vector_get (eval, i);
		gsl_vector_view evec_i = gsl_matrix_column (evec, i);
		std::cout<<"eigenvalue = "<<eval_i<<"\n";
		std::cout<<"eigenvector = \n";
		gsl_vector_fprintf (stdout, &evec_i.vector, "%g");
		std::cout<<"\n";
	}
	std::cout<<"\ninverse:\n";
	gsl_matrix *m_i = invert_matrix(m_data);
	gsl_matrix_fprintf(stdout, m_i, "%g");
	gsl_vector_free (eval);
	gsl_matrix_free (evec);
	gsl_matrix_free (m_data);
	gsl_matrix_free (m_i);
	return 0;
}
