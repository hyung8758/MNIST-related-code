#include "load_mnist.h"

int main(int argc, char *argv[]){
	unsigned int width, height;
	std::vector<unsigned char **> mnist_digits[10];
	if (argc == 3){
		load_mnist(argv[1], argv[2], width, height, mnist_digits);
		display_mnist_digit(width, height, mnist_digits[0][0]);
		free_mnist<unsigned char>(height, mnist_digits);
		return 0;
	}
	std::cout<<"Usage: "<<argv[0]<<" <name of image file> <name of label file>\n";
	return 0;
}
