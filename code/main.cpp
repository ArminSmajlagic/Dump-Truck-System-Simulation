//#include <iostream>;
//#include "RandomVariateGenerating.h"
//
////continue from 243 chapter 8.1.2 (Uniform distribution)
//
//void main() {
//
//	float R1[] = { 0.1306, 0.0422, 0.6597, 0.7965, 0.7696, 0.7791, 0.9211, 0.1862};
//
//	float R2[] = { 0.4357, 0.4146, 0.8353, 0.9953, 0.8004, 0.2892, 0.6533, 0.2398};
//
//	// For poisson; The range bellow represents time in minutes; The mean arrival time will be alfa = 32.5
//
//	int size = 8;
//
//	float* result_exp = RandVariateGenerator::Generate_Exponential_Varaiates(1, R1, size);
//	float* result_unif = RandVariateGenerator::Generate_Uniforme_Varaiates(20, 30, R1, size);
//	float* result_weibull = RandVariateGenerator::Generate_Weibull_Varaiates(3, 5, R1, size);
//	float* result_triangular = RandVariateGenerator::Generate_Triangular_Varaiates(R1, 5);
//	float* result_poisson = RandVariateGenerator::Generate_Poissson_Varaiates(0.38, R1, size);
//
//	printf("This are random variates for R1 data set : \n");
//
//	printf("\nPoisson by acceptence and rejection technique : \n");
//	for (int i = 0; i < 8; i++)
//	{
//		printf("%.4f", result_poisson[i]);
//		if (i != size - 1)
//			printf(" , ");
//	}
//	printf("\n");
//
//	printf("\nExponential by inverse transformation technique : \n");
//	for (int i = 0; i < size; i++)
//	{
//		printf("%.4f", result_exp[i]);
//		if (i != size - 1)
//			printf(" , ");
//	}
//	printf("\n");
//
//
//	printf("\nWeibull by inverse transformation technique : \n");
//	for (int i = 0; i < size; i++)
//	{
//		printf("%.4f", result_weibull[i]);
//		if (i != size - 1)
//			printf(" , ");
//	}
//	printf("\n");
//
//
//	printf("\nTriangular by inverse transformation technique : \n");
//	for (int i = 0; i < size; i++)
//	{
//		printf("%.4f", result_triangular[i]);
//		if (i != size - 1)
//			printf(" , ");
//	}
//	printf("\n");
//
//
//	printf("\nUnifrom by inverse transformation technique : \n");
//	for (int i = 0; i < size; i++)
//	{
//		printf("%.4f", result_unif[i]);
//		if (i != size - 1)
//			printf(" , ");
//	}
//	printf("\n");
//
//
//	result_exp = RandVariateGenerator::Generate_Exponential_Varaiates(1, R2, size);
//	result_unif = RandVariateGenerator::Generate_Uniforme_Varaiates(3, 5, R2, size);
//	result_weibull = RandVariateGenerator::Generate_Weibull_Varaiates(3, 5, R2, size);
//	result_triangular = RandVariateGenerator::Generate_Triangular_Varaiates(R2, 5);
//	result_poisson = RandVariateGenerator::Generate_Poissson_Varaiates(0.38, R2, size);
//
//	printf("\nThis are random variates for R2 data set : \n");
//
//	printf("\nPoisson by acceptence and rejection technique : \n");
//	for (int i = 0; i < 8; i++)
//	{
//		printf("%.4f", result_poisson[i]);
//		if (i != size - 1)
//			printf(" , ");
//	}
//	printf("\n");
//
//	printf("\nExponential by inverse transformation technique : \n");
//	for (int i = 0; i < size; i++)
//	{
//		printf("%.4f", result_exp[i]);
//		if (i != size - 1)
//			printf(" , ");
//	}
//	printf("\n");
//
//
//	printf("\nWeibull by inverse transformation technique : \n");
//	for (int i = 0; i < size; i++)
//	{
//		printf("%.4f", result_weibull[i]);
//		if (i != size - 1)
//			printf(" , ");
//	}
//	printf("\n");
//
//
//	printf("\nTriangular by inverse transformation technique : \n");
//	for (int i = 0; i < size; i++)
//	{
//		printf("%.4f", result_triangular[i]);
//		if (i != size - 1)
//			printf(" , ");
//	}
//	printf("\n");
//
//
//	printf("\nUnifrom by inverse transformation technique : \n");
//	for (int i = 0; i < size; i++)
//	{
//		printf("%.4f", result_unif[i]);
//		if (i != size - 1)
//			printf(" , ");
//	}
//	printf("\n");
//
//	int val;
//
//	std::cin >> val;
//
//	return;
//}