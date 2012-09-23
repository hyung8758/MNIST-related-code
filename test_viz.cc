#include "load_mnist.h"
#include "mnist_viz.h"

int main(int argc, char *argv[]){
	unsigned int width, height;
	std::vector<unsigned char **> mnist_digits[10];
	if (argc == 3){
		load_mnist(argv[1], argv[2], width, height, mnist_digits);
		for (unsigned int i = 0; i < 10; ++i){ 
			mnist_digit_2_png(width, height, mnist_digits[i][0], std::string("img_").append(1, '0' + i).append(".png").c_str());
		}
		free_mnist<unsigned char>(height, mnist_digits);
		return 0;
	}
	std::cout<<"Usage: "<<argv[0]<<" <name of image file> <name of label file>\n";
	return 0;
}
