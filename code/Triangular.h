#include <cmath>
#include <exception>
#include <string>

float* triangular_rand_gen(float R[], int size) {

	float* result = NULL;

	result = new float[size];

	
	for (int i = 0; i < size; i++)
	{
		if (R[i] > 0.000 && R[i] < 0.500) {
			result[i] = sqrt(R[i]*2);
		}
		else if(R[i] > 0.500 && R[i] < 1.000){
			result[i] = 2 - sqrt(2*(1-R[i]));
		}
		else if (R[i] > 1.000) {
			result[i] = 1;
		}
		else if (R[i] < 0.000) {
			result[i] = 0;
		}
		else {
			throw "The given Ri " + std::to_string(R[i]) + " doesnt fall in the range 0 and 1.";
		}
	}

	return result;
}
