#include <cmath>

class Result {
	float* R = NULL;
	float* Rejected_values = NULL;
	int c;
	int rej_c;
	int max;
public:
	Result()
	{
		max = 10;
		R = new float[max];
		Rejected_values = new float[max];
		c = 0;
		rej_c = 0;
	}

	void AddNewRVall(float NewRVal) {

		if (IsFull())
			Expand();

		R[c++] = NewRVal;
	}

	bool IsFull() {
		return max == c;
	}

	void Expand() {
		max *= 2;

		float* newR = new float[max];

		for (int i = 0; i < c; i++)
		{
			newR[i] = R[i];
		}

		R = newR;
	}

	float* GetR() {
		return R;
	}

	float GetVal(int i) {
		return R[i];
	}

	void SetVal(int i, float val) {
		R[i] = val;
	}

	float CalcP(float val) {

		Rejected_values[rej_c++] = val;

		float p = 1;

		for (int i = 0; i < rej_c; i++)
		{
			p *= Rejected_values[i];
		}

		return p;
	}

	void ClearRejectedValues() {
		for (int i = 0; i < rej_c; i++)
		{
			Rejected_values[i] = 0;
		}
		rej_c = 0;
	}

};


float* poisson_rand_gen(float alfa, float R[], int size) {

	Result result_ds = Result();

	float p;

	float exp_to_power_neg_alfa = exp(-alfa);
	
	for (int i = 0; i < size; i++)
	{
		result_ds.AddNewRVall(0);

		while (true) {

			p = result_ds.CalcP(R[i]);

			if (p < exp_to_power_neg_alfa) {
				result_ds.SetVal(i, p);
				result_ds.ClearRejectedValues();
				break;
			}
			result_ds.SetVal(i, -1);
			i++;
		}
	}

	return result_ds.GetR();
}


