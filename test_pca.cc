#include "load_mnist.h"
#include "pca.h"

#define NC 10

int main(int argc, char *argv[]){
	unsigned int width, height, k;
	std::vector<unsigned char **> mnist_digits[10];
	std::vector<unsigned char **> S;
	std::vector<unsigned char **>::const_iterator itr;
	if (argc == 3){
		load_mnist(argv[1], argv[2], width, height, mnist_digits, 10);
		for (k = 0; k < 10; ++k){
			for (itr = mnist_digits[k].begin(); itr != mnist_digits[k].end(); ++itr){
				S.push_back(*itr);
			}
		}
		pca <unsigned char>result(width, height, NC, S);
		free_mnist<unsigned char>(height, mnist_digits);
		return 0;
	}
	std::cout<<"Usage: "<<argv[0]<<" <name of image file> <name of label file>\n";
	return 0;
}
