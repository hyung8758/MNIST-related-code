#include "load_mnist.h"
#include "perceptron.h"



int main(int argc, char *argv[]){
	const unsigned int p0[] = {5, 0, 4, 6, 8, 9}, n0[] = {5, 1, 2, 3, 5, 7}, p1[] = {4, 0, 4, 6, 9}, n1[] = {1, 8}, p2[] = {2, 0, 4}, n2[] = {2, 6, 9}, p3[] = {1, 0}, n3[] = {1, 4}, p4[] = {1, 6}, n4[] = {1, 9}, p5[] = {4, 1, 2, 5, 7}, n5[] = {1, 3}, p6[] = {2, 1, 7}, n6[] = {2, 2, 5}, p7[] = {1, 1}, n7[] = {1, 7}, p8[] = {1, 2}, n8[] = {1, 5}, *partition[2][9] = {{p0, p1, p2, p3, p4, p5, p6, p7, p8}, {n0, n1, n2, n3, n4, n5, n6, n7, n8}};
	unsigned int width, height;
	std::vector<unsigned char **> mnist_digits[10];
	if (argc == 3){
		load_mnist(argv[1], argv[2], width, height, mnist_digits);
		for (unsigned int i = 0; i < 9; ++i){ 
			perceptron<unsigned char>(width, height, mnist_digits, partition[0][i], partition[1][i], 10000, .0001);
		}
		free_mnist<unsigned char>(height, mnist_digits);
		return 0;
	}
	std::cout<<"Usage: "<<argv[0]<<" <name of image file> <name of label file>\n";
	return 0;
}
