#include "libsvm/svm.h"
#include <iostream>

int main(int argc, char *argv[]){
	struct svm_problem prob;
	struct svm_parameter param;
	struct svm_node pt[3], *x_space;
	struct svm_model *model;
	double X[9][2] = {{1.5, 1.5}, {3.0, 3.0}, {1.0, 3.0}, {2.0, 2.5}, {1.0, 1.0}, {3.0, 1.0}, {3.0, 2.5}, {4.0, 3.0}, {1.0, 2.0}};
	int i, j, Y[9] = {1, 1, 1, 1, -1, -1, -1, -1, -1};
	x_space = new struct svm_node[27];
	prob.l = 9;
	prob.y = new double[9];
	prob.x = new struct svm_node*[9];
	for (i = 0; i < 9; ++i){
		prob.y[i] = Y[i];
		x_space[3 * i].index = 1;
		x_space[3 * i].value = X[i][0];
		x_space[3 * i + 1].index = 2;
		x_space[3 * i + 1].value = X[i][1];
		x_space[3 * i + 2].index = -1;
		prob.x[i] = x_space + 3 * i;
	}
	param.svm_type = C_SVC;
	param.kernel_type = RBF;
	//param.degree = 3;
	param.gamma = 0.5;
	param.coef0 = 0;
	//param.nu = 0.5;
	param.cache_size = 100;
	param.C = 10.0;
	param.eps = 1e-3;
	param.p = 0.1;
	param.shrinking = 1;
	param.probability = 0;
	param.nr_weight = 0;
	param.weight_label = 0;
	param.weight = 0;
	model = svm_train(&prob, &param);
	pt[0].index = 1; 
	pt[1].index = 2;
	pt[2].index = -1;
	for (i = 59; i >= 0; --i){
		pt[1].value = i * 1.0 / 10;
		for (j = -10; j < 60; ++j){
			pt[0].value = j * 1.0 / 10;
			std::cout<<(svm_predict(model, pt) > 0 ? '+' : '-')<<",";
		}
		std::cout<<"\n";
	}
	svm_free_and_destroy_model(&model);
	delete [] x_space;
	delete [] prob.y;
	delete [] prob.x;
	return 0;
}
