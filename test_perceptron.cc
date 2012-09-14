#include "load_mnist.h"
#include "perceptron.h"

#define VERBOSE false 
#define MAX_ITER 200

static const unsigned int p0[] = {5, 0, 4, 6, 8, 9}, n0[] = {5, 1, 2, 3, 5, 7}, p1[] = {4, 0, 4, 6, 9}, n1[] = {1, 8}, p2[] = {2, 0, 4}, n2[] = {2, 6, 9}, p3[] = {1, 0}, n3[] = {1, 4}, p4[] = {1, 6}, n4[] = {1, 9}, p5[] = {4, 1, 2, 5, 7}, n5[] = {1, 3}, p6[] = {2, 1, 7}, n6[] = {2, 2, 5}, p7[] = {1, 1}, n7[] = {1, 7}, p8[] = {1, 2}, n8[] = {1, 5}, *partition[2][9] = {{p0, p1, p2, p3, p4, p5, p6, p7, p8}, {n0, n1, n2, n3, n4, n5, n6, n7, n8}};

unsigned int perceptron(const unsigned int, const unsigned int, double * const[], unsigned char ** const);
bool f(const unsigned int, const unsigned int, const double *, unsigned char ** const); 

int main(int argc, char *argv[]){
	unsigned int i, j, score, m, training_width, training_height, testing_width, testing_height;
	double *w[9];
	double alpha[9] = {7.5e-11, 1e-10, 1e-10, 7.5e-11, 1e-10, 1e-10, 1e-10, 1e-10, 5e-11};
	double rtol[9] = {.1, .025, .05, .025, .025, .025, .025, .025, .025};
	std::vector<unsigned char **> training_mnist_digits[10], testing_mnist_digits[10];
	srand(time(0));
	if (argc == 5){
		load_mnist(argv[1], argv[2], training_width, training_height, training_mnist_digits);
		m = training_width * training_height;
		for (i = 0; i < 9; ++i){ 
			w[i] = perceptron<unsigned char>(training_width, training_height, training_mnist_digits, partition[0][i], partition[1][i], MAX_ITER, rtol[i], alpha[i], VERBOSE);
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
			delete [] w[i];
		}
		return 0;
	}
	std::cout<<"Usage: "<<argv[0]<<" <name of training image file> <name of training label file> <name of testing image file> <name of testing label file>\n";
	return 0;
}

unsigned int perceptron(const unsigned int width, const unsigned int height, double * const w[], unsigned char ** const img){
	if (f(width, height, w[0], img)){
		if (f(width, height, w[1], img)){
			if (f(width, height, w[2], img)){
				return f(width, height, w[3], img) ? 0 : 4;
			}else{
				return f(width, height, w[4], img) ? 6 : 9;
			}
		}else{
			return 8;
		}
	}else{
		if (f(width, height, w[5], img)){
			if (f(width, height, w[6], img)){
				return f(width, height, w[7], img) ? 1 : 7;
			}else{
				return f(width, height, w[8], img) ? 2 : 5;
			}
		}else{
			return 3;
		}
	}
}

bool f(const unsigned int width, const unsigned int height, const double *w, unsigned char ** const img){
	double y = 0.0;
	for (unsigned int i = 0; i < height; ++i){
		for (unsigned int j = 0; j < width; ++j, ++w){
			y += *w * img[i][j];
		}
	}
	y += *w;
	return y >= 0;
}
