#include "load_mnist.h"
#include "pca.h"
#include "mnist_viz.h"
#include <sstream>
#include <string>

#define NC 10
#define K 3

int main(int argc, char *argv[]){
	unsigned int width, height, i, j, nS;
	unsigned char **p;
	double **mean, **current_img;
	std::vector<unsigned char **> mnist_digits[10];
	std::vector<double **> S;
	std::vector<unsigned char **>::const_iterator itr;
	if (argc == 3){
		load_mnist(argv[1], argv[2], width, height, mnist_digits, 100);
		p = new unsigned char*[height];
		mean = new double*[height];
		for (i = 0; i < height; ++i){
			p[i] = new unsigned char[width];
			mean[i] = new double[width];
			for (j = 0; j < width; ++j){
				mean[i][j] = 0.0;
			}
		}
		//for (k = 0; k < 10; ++k){
		nS = mnist_digits[K].size();
		for (itr = mnist_digits[K].begin(); itr != mnist_digits[K].end(); ++itr){
			for (i = 0; i < height; ++i){
				for (j = 0; j < width; ++j){
					mean[i][j] += (*itr)[i][j] * 1.0 / nS;
				}
			}
			//S.push_back(*itr);
		}
		for (itr = mnist_digits[K].begin(); itr != mnist_digits[K].end(); ++itr){
			current_img = new double*[height];
			for (i = 0; i < height; ++i){
				current_img[i] = new double[width];
				for (j = 0; j < width; ++j){
					current_img[i][j] = (*itr)[i][j] - mean[i][j];
				}
			}
			S.push_back(current_img);
		}
		pixelize<double>(width, height, mean, p);
		mnist_digit_2_png(width, height, p, "mean.png");
		pca <double>result(width, height, NC, S);
		for (i = 0; i < NC; ++i){
			std::stringstream s;
			s<<i;
			pixelize<double>(width, height, result.get_pc(i), p);
			mnist_digit_2_png(width, height, p, std::string("evec_").append(s.str()).append(".png").c_str());
		}
		free_mnist<unsigned char>(height, mnist_digits);
		free_mnist<double>(height, S);
		for (i = 0; i < height; ++i){
			delete [] p[i];
			delete [] mean[i];
		}
		delete [] p;
		delete [] mean;
		return 0;
	}
	std::cout<<"Usage: "<<argv[0]<<" <name of image file> <name of label file>\n";
	return 0;
}
