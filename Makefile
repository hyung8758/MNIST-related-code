CC=g++
CFLAGS=-Wall -O3 
LDFLAGS=
TEST_LOAD_MNIST=test_load_mnist.o
TEST_PERCEPTRON_ALT=test_perceptron_alt.o
OBJECTS=$(SOURCES:.cc=.o)
EXECUTABLES=test_load_mnist test_perceptron_alt

.PHONY: clean

.cc.o:
	$(CC) $(CFLAGS) -c $<

test_load_mnist: $(TEST_LOAD_MNIST)
	$(CC) $(CFLAGS) $(TEST_LOAD_MNIST) -o $@

test_perceptron_alt: $(TEST_PERCEPTRON_ALT)
	$(CC) $(CFLAGS) $(TEST_PERCEPTRON_ALT) -o $@

clean:
	rm -rf *.o $(EXECUTABLES)
