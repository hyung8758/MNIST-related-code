#include "load_mnist.h"
#include "perceptron.h"

#define VERBOSE true 
#define MAX_ITER 200
#define TOL .04
#define ALPHA 1e-11

unsigned int perceptron(const unsigned int, const unsigned int, double *[10][10], unsigned char ** const);

int main(int argc, char *argv[]){
	unsigned int i, j, score, m, training_width, training_height, testing_width, testing_height, p[2], n[2];
	double *w[10][10];
	std::vector<unsigned char**> training_mnist_digits[10], testing_mnist_digits[10];
	srand(time(0));
	if (argc == 5){
		load_mnist(argv[1], argv[2], training_width, training_height, training_mnist_digits);
		m = training_width * training_height;
		p[0] = 1;
		n[0] = 1;
		for (i = 0; i < 9; ++i){ 
			p[1] = i;
			for (j = i + 1; j < 10; ++j){
				n[1] = j;
				w[i][j] = perceptron<unsigned char>(training_width, training_height, training_mnist_digits, p, n, MAX_ITER, TOL, ALPHA, VERBOSE);
			}
		}
		free_mnist<unsigned char>(training_height, training_mnist_digits);
		load_mnist(argv[1], argv[2], testing_width, testing_height, testing_mnist_digits);
		if (training_width != testing_width || training_height != testing_height){
			std::cout<<"warning: training set and testing set have different dimensions\n";
		}
		for (i = 0; i < 10; ++i){
			score = 0;
			std::cout<<"\nrunning random test cases for "<<i<<"\n";
			for (j = 0; j < 100; ++j){
				if (perceptron(testing_width, testing_height, w, testing_mnist_digits[i][rand() % testing_mnist_digits[i].size()]) == i){
					++score;
				}
				//std::cout<<"test result: "<<perceptron(testing_width, testing_height, w, testing_mnist_digits[i][rand() % testing_mnist_digits[i].size()])<<"\n";
			}
			std::cout<<"test score for "<<i<<": "<<score<<"/100\n"; 
		}
		free_mnist<unsigned char>(testing_height, testing_mnist_digits);
		for (i = 0; i < 9; ++i){ 
			for (j = i + 1; j < 10; ++j){
				delete [] w[i][j];
			}
		}
		return 0;
	}
	std::cout<<"Usage: "<<argv[0]<<" <name of training image file> <name of training label file> <name of testing image file> <name of testing label file>\n";
	return 0;
}

unsigned int perceptron(const unsigned int width, const unsigned int height, double *w[10][10], unsigned char ** const img){
	bool recognized;
	unsigned int i, j; 
	for (i = 0; i < 9; ++i){
		recognized = true;
		for (j = i + 1; j < 10; ++j){
			if (!f<unsigned char>(width, height, w[i][j], img)){
				recognized = false;
				break;
			}
		}
		if (recognized){
			return i;
		}
	}
	return 9;
}
