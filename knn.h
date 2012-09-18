#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#define DEFAULT_LAMBDA .1    //the regularization coefficient for the |w|^2 term
#define G_RAD 1.0

#include <vector>
#include <queue>
#include "misc.h"

/* code for computing decision boundary with the regularized least square rule and some feature-mapping function */

struct compare_dist{
	bool operator()(const std::pair<unsigned int, double> &a, const std::pair<unsigned int, double> &b){
		return a.second > b.second;
	}
};

template <typename T>
class knn{
	private:
		unsigned int width, height, N, K;
		const std::vector<T**> *S;
	public:
		knn(const unsigned int _width, const unsigned int _height, const unsigned int _N, const unsigned int _K, const std::vector<T**> _S[]) : width(_width), height(_height), N(_N), K(_K), S(_S){}

		unsigned int mlc(T ** const x) const{
			unsigned int i, m, mk;
			unsigned int *v = new unsigned int[K];
			typename std::vector<T**>::const_iterator itr;
			std::priority_queue< std::pair<unsigned int, double>, std::vector< std::pair<unsigned int, double> >, compare_dist > q;
			for (i = 0; i < N; ++i){
				for (itr = S[i].begin(); itr != S[i].end(); ++itr){
					q.push(std::pair<unsigned int, double>(i, dist2<T>(width, height, x, *itr))); 
				}
			}
			for (i = 0; i < K; ++i){
				v[i] = 0;
			}
			for (i = 0; i < K; ++i){
				++v[q.top().first];
				q.pop();
			}
			m = v[0];
			mk = 0;
			for (i = 1; i < K; ++i){
				if (v[i] > m){
					m = v[i];
					mk = i;
				}
			}
			delete [] v;
			return mk;
		}

};

#endif
