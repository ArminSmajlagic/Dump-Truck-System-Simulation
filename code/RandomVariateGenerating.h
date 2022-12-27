#include "Exponential.h"
#include "Gamma.h"
#include "Geometrical.h"
#include "Poisson.h"
#include "Triangular.h"
#include "Uniform.h"
#include "Weibull.h"

static class RandVariateGenerator {
public:
	static float* Generate_Exponential_Varaiates(float lambda, float* R, int size) {
		return exponential_rand_gen(lambda, R, size);
	}

	static float* Generate_Uniforme_Varaiates(float a, float b, float* R, int size) {
		return uniform_rand_gen(a, b, R, size);
	}

	static float* Generate_Weibull_Varaiates(float alfa, float beta, float* R, int size) {
		return weibull_rand_gen(alfa, beta, R, size);
	}

	static float* Generate_Triangular_Varaiates(float* R, int size) {
		return triangular_rand_gen(R, size);
	}

	// Acceptence-Rejection Techniques

	static float* Generate_Poissson_Varaiates(float alfa, float* R, int size) {
		return poisson_rand_gen(alfa, R, size);
	}
};