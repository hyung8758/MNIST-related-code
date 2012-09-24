#include "load_mnist.h"
#include "pca.h"
#include "mnist_viz.h"
#include <string>

#define NC 10

int main(int argc, char *argv[]){
	unsigned int width, height, i, k;
	unsigned char **p;
	std::vector<double **> mnist_digits[10];
	std::vector<double **> S;
	std::vector<double **>::const_iterator itr;
	if (argc == 3){
		load_normalized_mnist(argv[1], argv[2], width, height, mnist_digits, false, 100);
		p = new unsigned char*[height];
		for (i = 0; i < height; ++i){
			p[i] = new unsigned char[width];
		}
		for (k = 0; k < 10; ++k){
			for (itr = mnist_digits[k].begin(); itr != mnist_digits[k].end(); ++itr){
				S.push_back(*itr);
			}
		}
		pca <double>result(width, height, NC, S);
		result.print_pc();
		for (k = 0; k < 10; ++k){
			pixelize<double>(width, height, result.get_pc(k), p);
			mnist_digit_2_png(width, height, p, std::string("evec_").append(1, '0' + k).append(".png").c_str());
		}
		free_mnist<double>(height, mnist_digits);
		for (i = 0; i < height; ++i){
			delete [] p[i];
		}
		delete [] p;
		return 0;
	}
	std::cout<<"Usage: "<<argv[0]<<" <name of image file> <name of label file>\n";
	return 0;
}
