#include <cmath>

float* weibull_rand_gen(float alfa, float beta, float R[], int size) {

	float* result = NULL;

	result = new float[size];

	for (int i = 0; i < size; i++)
	{
		float logarithm = log(1 - R[i]);
		float exponent = 1 / beta;
		result[i] = alfa * pow(-logarithm, exponent);
	}

	return result;
}
