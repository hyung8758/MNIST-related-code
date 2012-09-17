CC=g++
CFLAGS=-c -Wall -O3 
LDFLAGS=
TEST_LIBGSL=test_libgsl.o
TEST_PNG_UTIL=test_png_util.o
TEST_LOAD_MNIST=test_load_mnist.o
TEST_PERCEPTRON=test_perceptron.o
TEST_PERCEPTRON_ALT=test_perceptron_alt.o
TEST_NAIVE_BAYES=test_naive_bayes.o
TEST_REG_LSE=test_reg_lse.o
OBJECTS=$(SOURCES:.cc=.o)
EXECUTABLES=test_libgsl test_png_util test_load_mnist test_perceptron test_perceptron_alt test_naive_bayes test_reg_lse

.PHONY: clean

.cc.o:
	$(CC) $(CFLAGS) $<

all: $(EXECUTABLES)

test_libgsl: $(TEST_LIBGSL)
	$(CC) $(LDFLAGS) `pkg-config --libs gsl` $(TEST_LIBGSL) -o $@

test_png_util: $(TEST_PNG_UTIL)
	$(CC) $(LDFLAGS) `pkg-config --libs libpng` $(TEST_PNG_UTIL) -o $@

test_load_mnist: $(TEST_LOAD_MNIST)
	$(CC) $(LDFLAGS) $(TEST_LOAD_MNIST) -o $@

test_perceptron: $(TEST_PERCEPTRON)
	$(CC) $(LDFLAGS) $(TEST_PERCEPTRON) -o $@

test_perceptron_alt: $(TEST_PERCEPTRON_ALT)
	$(CC) $(LDFLAGS) $(TEST_PERCEPTRON_ALT) -o $@

test_naive_bayes: $(TEST_NAIVE_BAYES)
	$(CC) $(LDFLAGS) $(TEST_NAIVE_BAYES) -o $@

test_reg_lse: $(TEST_REG_LSE)
	$(CC) $(LDFLAGS) `pkg-config --libs gsl` $(TEST_REG_LSE) -o $@

clean:
	rm -rf *.o $(EXECUTABLES) *.png
