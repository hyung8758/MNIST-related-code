#include "libsvm/svm.h"
#include "load_mnist.h"

int main(int argc, char *argv[]){
	unsigned int i, j, k, l, m, t, p, score, training_width, training_height, testing_width, testing_height;
	std::vector<double**> training_mnist_digits[10], testing_mnist_digits[10];
	struct svm_problem prob;
	struct svm_parameter param;
	struct svm_node *pt, *x_space;
	struct svm_model *model;
	srand(time(0));
	if (argc == 5){
		load_normalized_mnist(argv[1], argv[2], training_width, training_height, training_mnist_digits, false, 20);  //note: technically should use same the normalization of the training data if the source of testing data is different from the source of the testing data 
		m = training_width * training_height + 1;
		pt = new svm_node[m];
		for (k = 0, l = 0; k < 10; ++k){
			l += training_mnist_digits[k].size();
		}
		prob.l = l;
		prob.y = new double[l];
		prob.x = new struct svm_node*[l];
		x_space = new struct svm_node[l * m];
		t = 0;
		for (k = 0; k < 10; ++k){
			for (std::vector<double**>::const_iterator itr = training_mnist_digits[k].begin(); itr != training_mnist_digits[k].end(); ++itr, ++t){		
				prob.y[t] = k;
				p = 0;
				for (i = 0; i < training_height; ++i){
					for (j = 0; j < training_width; ++j, ++p){
						x_space[m * t + p].index = p + 1;   //note: index is 1-based
						x_space[m * t + p].value = (*itr)[i][j];
					}
				}
				x_space[m * t + p].index = -1;
				prob.x[t] = x_space + m * t;
				prob.y[t] = k;
			}
		}
		param.svm_type = C_SVC;
		param.kernel_type = RBF;
		param.gamma = 0.5;
		param.coef0 = 0;
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
		load_normalized_mnist(argv[1], argv[2], testing_width, testing_height, testing_mnist_digits, false, 20);
		if (training_width != testing_width || training_height != testing_height){
			std::cout<<"warning: training set and testing set have different dimensions\n";
		}
		for (k = 0; k < 10; ++k){
			score = 0;
			for (l = 0; l < 100; ++l){
				double **tc = testing_mnist_digits[k][rand() % testing_mnist_digits[k].size()];
				p = 0;
				for (i = 0; i < training_height; ++i){
					for (j = 0; j < training_width; ++j, ++p){
						pt[p].index = p + 1;   //note: index is 1-based
						pt[p].value = tc[i][j];
					}
				}
				pt[p].index = -1; 
				if (svm_predict(model, pt) == k){
					++score;
				}
			}
			std::cout<<"test score for "<<k<<": "<<score<<"/100\n";
		}
		free_mnist<double>(training_height, training_mnist_digits);
		free_mnist<double>(testing_height, testing_mnist_digits);
		svm_free_and_destroy_model(&model);
		delete [] x_space;
		delete [] pt; 
		delete [] prob.y;
		delete [] prob.x;
		return 0;
	}
	std::cout<<"Usage: "<<argv[0]<<" <name of training image file> <name of training label file> <name of testing image file> <name of testing label file>\n";
	return 0;
}
