#ifndef MISC_H
#define MISC_H

#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include <gsl/gsl_math.h>

std::string partition_str(const unsigned int pt[]){
	unsigned int i;
	std::string ret = "{";
	for (i = 1; i < pt[0]; ++i){
		ret += pt[i] + '0';
		ret += ", ";
	}
	ret += pt[i] + '0';
	ret += "}";
	return ret;
}

void rand_permute(unsigned int m, unsigned int a[]){
	unsigned int i, j;
	srand (time(0));
	a[0] = 0;
	for (i = 1; i < m; ++i){
		if ( (j = rand() % (i + 1)) != i ){
			a[i] = a[j];
			a[j] = i;
		}else{
			a[i] = i;
		}
	}
}

#endif
