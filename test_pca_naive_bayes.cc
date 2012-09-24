#include "load_mnist.h"
#include "naive_bayes.h"
#include "pca.h"

#define N 700    //number of principal components

int main(int argc, char *argv[]){
	unsigned int i, j, k, score, training_width, training_height, testing_width, testing_height;
	std::vector<double **> training_mnist_digits[10], testing_mnist_digits[10], pca_training_mnist_digits[10], pca_testing_mnist_digits[10], S;
	std::vector<double **>::iterator itr;
	srand(time(0));
	if (argc == 5){
		load_mnist_for_pca(argv[1], argv[2], training_width, training_height, training_mnist_digits, 100);
		load_mnist_for_pca(argv[1], argv[2], testing_width, testing_height, testing_mnist_digits);
		if (training_width != testing_width || training_height != testing_height){
			std::cout<<"warning: training data and testing data have different dimensions\n";
		}
		for (k = 0; k < 10; ++k){
			for (itr = training_mnist_digits[k].begin(); itr != training_mnist_digits[k].end(); ++itr){
				S.push_back(*itr);
			}
		}
		pca<double> result(training_width, training_height, N, S);
		for (k = 0; k < 10; ++k){
			for (itr = training_mnist_digits[k].begin(); itr != training_mnist_digits[k].end(); ++itr){
				double **p_img = new double*[1];
				p_img[0] = result.proj(*itr);
				pca_training_mnist_digits[k].push_back(p_img);
			}
		}
		for (k = 0; k < 10; ++k){
			for (itr = testing_mnist_digits[k].begin(); itr != testing_mnist_digits[k].end(); ++itr){
				double **p_img = new double*[1];
				p_img[0] = result.proj(*itr);
				pca_testing_mnist_digits[k].push_back(p_img);
			}
		}
		naive_bayes<double> c(N, 1, 10, pca_training_mnist_digits);
		for (i = 0; i < 10; ++i){
			score = 0;
			std::cout<<"\nrunning random test cases for "<<i<<"\n";
			for (j = 0; j < 100; ++j){
				if (c.mlc(pca_testing_mnist_digits[i][rand() % pca_testing_mnist_digits[i].size()]) == i){
					++score;
				}
				//std::cout<<"test result: "<<perceptron(testing_width, testing_height, w, testing_mnist_digits[i][rand() % testing_mnist_digits[i].size()])<<"\n";
			}
			std::cout<<"test score for "<<i<<": "<<score<<"/100\n"; 
		}
		free_mnist<double>(training_height, training_mnist_digits);
		free_mnist<double>(testing_height, testing_mnist_digits);
		free_mnist<double>(1, pca_training_mnist_digits);
		free_mnist<double>(1, pca_testing_mnist_digits);
		return 0;
	}
	std::cout<<"Usage: "<<argv[0]<<" <name of training image file> <name of training label file> <name of testing image file> <name of testing label file>\n";
	return 0;
}
