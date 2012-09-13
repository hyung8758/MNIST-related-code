#include "load_mnist.h"
#include "perceptron.h"

int main(int argc, char *argv[]){
	unsigned int i, width, height;
	std::vector<unsigned char **> mnist_digits[10];
	const std::vector<unsigned char **>* m[10][1];
	const std::vector<unsigned char **>* m_0_4_6_8_9[] = {mnist_digits + 0, mnist_digits + 4, mnist_digits + 6, mnist_digits + 8, mnist_digits + 9};
	const std::vector<unsigned char **>* m_0_4_6_9[] = {mnist_digits + 0, mnist_digits + 4, mnist_digits + 6, mnist_digits + 9};
	const std::vector<unsigned char **>* m_0_4[] = {mnist_digits + 0, mnist_digits + 4};
	const std::vector<unsigned char **>* m_6_9[] = {mnist_digits + 6, mnist_digits + 9};
	const std::vector<unsigned char **>* m_1_2_3_5_7[] = {mnist_digits + 1, mnist_digits + 2, mnist_digits + 3, mnist_digits + 5, mnist_digits + 7};
	const std::vector<unsigned char **>* m_1_2_5_7[] = {mnist_digits + 1, mnist_digits + 2, mnist_digits + 5, mnist_digits + 7};
	const std::vector<unsigned char **>* m_1_7[] = {mnist_digits + 1, mnist_digits + 7};
	const std::vector<unsigned char **>* m_2_5[] = {mnist_digits + 2, mnist_digits + 5};
	for (i = 0; i < 10; ++i){
		m[i][0] = mnist_digits + i;
	}
	if (argc == 3){
		load_mnist(argv[1], argv[2], width, height, mnist_digits);
		std::cout<<"separating {0, 4, 6, 8, 9} and {1, 2, 3, 5, 7}:\n\n";
		perceptron<unsigned char>(width, height, m_0_4_6_8_9, m_1_2_3_5_7, 10000, .0001);	
		std::cout<<"\nseparating {8} and {0, 4, 6, 9}:\n\n";
		perceptron<unsigned char>(width, height, m[8], m_0_4_6_9, 10000, .0001);	
		std::cout<<"\nseparating {0, 4} and {6, 9}:\n\n";
		perceptron<unsigned char>(width, height, m_0_4, m_6_9, 10000, .0001);	
		std::cout<<"\nseparating {0} and {4}:\n\n";
		perceptron<unsigned char>(width, height, m[0], m[4], 10000, .0001);	
		std::cout<<"\nseparating {6} and {9}:\n\n";
		perceptron<unsigned char>(width, height, m[6], m[9], 10000, .0001);	
		std::cout<<"\nseparating {3} and {1, 2, 5, 7}:\n\n";
		perceptron<unsigned char>(width, height, m[3], m_1_2_5_7, 10000, .0001);	
		std::cout<<"\nseparating {1, 7} and {2, 5}:\n\n";
		perceptron<unsigned char>(width, height, m_1_7, m_2_5, 10000, .0001);	
		std::cout<<"\nseparating {2} and {5}:\n\n";
		perceptron<unsigned char>(width, height, m[2], m[5], 10000, .0001);	
		std::cout<<"\nseparating {1} and {7}:\n\n";
		perceptron<unsigned char>(width, height, m[1], m[7], 10000, .0001);	
		free_mnist<unsigned char>(height, mnist_digits);
		return 0;
	}
	std::cout<<"Usage: "<<argv[0]<<" <name of image file> <name of label file>\n";
	return 0;
}
