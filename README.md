MNIST-related-code
==================

this repository contains code for some simple experiments with the MNIST dataset

NOTE: it appears that SVM is the best approach in terms of generalizing to the entire dataset

for exmaple: one can test this method with these steps: 

make clean && make test_svm

./test_svm train-images-idx3-ubyte train-labels-idx1-ubyte t10k-images-idx3-ubyte t10k-labels-idx1-ubyte
