CC=g++
CFLAGS=-c -Wall -O3 
LDFLAGS=
TEST_LOAD_MNIST=test_load_mnist.o
TEST_PERCEPTRON=test_perceptron.o
TEST_PERCEPTRON_ALT=test_perceptron_alt.o
TEST_NAIVE_BAYES=test_naive_bayes.o
OBJECTS=$(SOURCES:.cc=.o)
EXECUTABLES=test_load_mnist test_perceptron test_perceptron_alt test_naive_bayes

.PHONY: clean

.cc.o:
	$(CC) $(CFLAGS) $<

all: $(EXECUTABLES)

test_load_mnist: $(TEST_LOAD_MNIST)
	$(CC) $(LDFLAGS) $(TEST_LOAD_MNIST) -o $@

test_perceptron: $(TEST_PERCEPTRON)
	$(CC) $(LDFLAGS) $(TEST_PERCEPTRON) -o $@

test_perceptron_alt: $(TEST_PERCEPTRON_ALT)
	$(CC) $(LDFLAGS) $(TEST_PERCEPTRON_ALT) -o $@

test_naive_bayes: $(TEST_NAIVE_BAYES)
	$(CC) $(LDFLAGS) $(TEST_NAIVE_BAYES) -o $@

clean:
	rm -rf *.o $(EXECUTABLES)
