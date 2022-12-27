#include <cmath>

float* exponential_rand_gen(float lambda, float R[], int size);

float* exponential_rand_gen(float lambda, float R[], int size) {

	float *result = NULL;

	result = new float[size];

	for (int i = 0; i < size; i++)
	{
		result[i] = -((1 / lambda) * log(1 - R[i]));
	}
	
	return result;
}