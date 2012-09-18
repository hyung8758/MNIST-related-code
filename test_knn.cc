#include "load_mnist.h"
#include "knn.h"

int main(int argc, char *argv[]){
	unsigned int i, j, score, training_width, training_height, testing_width, testing_height;
	std::vector<double **> training_mnist_digits[10], testing_mnist_digits[10];
	srand(time(0));
	if (argc == 5){
		load_normalized_mnist(argv[1], argv[2], training_width, training_height, training_mnist_digits, 400);
		load_normalized_mnist(argv[1], argv[2], testing_width, testing_height, testing_mnist_digits);
		if (training_width != testing_width || training_height != testing_height){
			std::cout<<"warning: training data and testing data have different dimensions\n";
		}
		knn<double> c(training_width, training_height, 10, 40, training_mnist_digits);
		for (i = 0; i < 10; ++i){
			score = 0;
			std::cout<<"\nrunning random test cases for "<<i<<"\n";
			for (j = 0; j < 100; ++j){
				if (c.mlc(testing_mnist_digits[i][rand() % testing_mnist_digits[i].size()]) == i){
					++score;
				}
				//std::cout<<"test result: "<<perceptron(testing_width, testing_height, w, testing_mnist_digits[i][rand() % testing_mnist_digits[i].size()])<<"\n";
			}
			std::cout<<"test score for "<<i<<": "<<score<<"/100\n"; 
		}
		free_mnist<double>(testing_height, testing_mnist_digits);
		free_mnist<double>(training_height, training_mnist_digits);
		return 0;
	}
	std::cout<<"Usage: "<<argv[0]<<" <name of training image file> <name of training label file> <name of testing image file> <name of testing label file>\n";
	return 0;
}
