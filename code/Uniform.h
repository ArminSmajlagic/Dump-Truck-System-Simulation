#include <cmath>

float* uniform_rand_gen(float a, float b, float *R, int size) {

	float* result = NULL;

	result = new float[size];

	for (int i = 0; i < size; i++)
	{
		result[i] = a + (b - a) * R[i];
	}

	return result;
}