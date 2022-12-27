#include <iostream>;
#include "RandomVariateGenerating.h"

//Initial Data
int number_of_trucks = 8;
int number_of_weighters = 2;
int number_of_loaders = 3;

//Initial time mesurements
int cumulativ_weighting_time = 0;
int cumulativ_loading_time = 0;
int global_clock = 0;

//Performance mesurements
float coef_of_weighters_util = 0.000;
float coef_of_loaders_util = 0.000;

//Enumaration to help identify different components of simulation

enum location {
	LOADER = 1,
	WEIGHTER = 2,
	ROAD = 3,
	LQ = 4,
	WQ = 5
};

enum truck_numbers {
	TR_DOESNT_EXIST = 0,
	TR1 = 1,
	TR2 = 2,
	TR3 = 3,
	TR4 = 4,
	TR5 = 5,
	TR6 = 6,
	TR7 = 7,
	TR8 = 8,
};

enum loader_number {
	LDR1 = 1,
	LDR2 = 2,
	LDR3 = 3
};

enum weighter_number
{
	WGHTR1 = 1,
	WGHTR2 = 2,
};

enum event_type {
	EL = 1,
	EW = 2,
	ALQ = 3,
	ELQ = 4,
	AWQ = 5,
	EWQ = 6
};

//Components of simulation

class Truck{
public:
	truck_numbers id;
	location current_location;
	int* loading_series;
	int* weighting_series;
	int* traveling_series;
	int cycle;
	int number_of_cycles;


	Truck()
	{
		current_location = LQ;
		id = TR_DOESNT_EXIST;
		loading_series = new int[5];
		weighting_series = new int[5];
		traveling_series = new int[5];
		cycle = 1;
		number_of_cycles = 1;
	}

	void InitTruck(truck_numbers num, int loading, int weighting, int traveling, location loc = LQ, int cycles = 1) {
		current_location = loc;
		id = num;
		number_of_cycles = cycles;
		
		loading_series[0] = loading;
		weighting_series[0] = weighting;
		traveling_series[0] = traveling;
	}

	int CurrentLoading() {
		return loading_series[cycle-1];
	}

	int CurrentWeighting() {
		return weighting_series[cycle-1];
	}

	int CurrentTraveling() {
		return traveling_series[cycle-1];
	}

	int IterateSimulationCycle() {
		cycle++;
	}

	int CumulativLoading() {
		int cumul_sum = 0;
		for (int i = 0; i < cycle; i++)
		{
			cumul_sum += loading_series[i];
		}
		return cumul_sum;
	}

	int CumulativWeighting() {
		int cumul_sum = 0;
		for (int i = 0; i < cycle; i++)
		{
			cumul_sum += weighting_series[i];
		}
		return cumul_sum;
	}

	int CumulativTraveling() {
		int cumul_sum = 0;
		for (int i = 0; i < cycle; i++)
		{
			cumul_sum += traveling_series[i];
		}
		return cumul_sum;
	}

	bool IsInWhichLocation(location loc) {
		return current_location = loc;
	}

	Truck operator= (Truck tr) {
		id = tr.id;
		current_location = tr.current_location;
		cycle = tr.cycle;
		for (int i = 0; i < tr.number_of_cycles; i++)
		{
			loading_series[i] = tr.loading_series[i];
			weighting_series[i] = tr.weighting_series[i];
			//traveling_series[i] = tr.traveling_series[i];
		}

		return *this;
	}

	void Print() {

		printf("\n+ Truck ");
		printf("%d",(int)id);

		printf(": \n Loading time ->");
		printf("%d", (int)round(loading_series[0]));

		printf("\n Weightng time ->");
		printf("%d", (int)round(weighting_series[0]));

		printf("\n Traveling time ->");
		printf("%d", (int)round(traveling_series[0]));

		printf("\n");
	}
};

class WeightingQueue {
public:
	Truck* trucks;
	int tr_count;

	WeightingQueue()
	{
		tr_count = 0;
		trucks = new Truck[number_of_trucks];
	}

	void Enqueue(Truck tr) {
		if (IsFull()) {
			printf("Weighting queue is full");
			return;
		}
		trucks[tr_count++] = tr;
	}

	Truck Dequeue() {

		if (IsEmpty()) {
			printf("Weighting queue is empty");
			return Truck();
		}

		Truck tr = Truck();

		tr = trucks[0];

		tr_count--;

		for (int i = 0; i < tr_count; i++)
		{
			trucks[i] = trucks[i + 1];
		}


		return tr;
	}

	bool IsFull() {
		return tr_count == number_of_trucks;
	}

	bool IsEmpty() {
		return tr_count == 0;
	}

	bool HasAny() {
		return tr_count > 0;
	}
};

class LoadingQueue {
public:
	Truck* trucks;
	int tr_count;

	LoadingQueue()
	{
		tr_count = 0;
		trucks = new Truck[number_of_trucks];
	}

	void Enqueue(Truck tr) {
		if (IsFull()) {
			printf("Loading queue is full");
			return;
		}
		trucks[tr_count++] = tr;
	}

	Truck Dequeue() {

		if (IsEmpty()) {
			printf("Loading queue is empty");
			return Truck();
		}

		Truck tr = Truck();

		tr = trucks[0];

		tr_count--;

		for (int i = 0; i < tr_count; i++)
		{
			trucks[i] = trucks[i + 1];
		}


		return tr;
	}

	bool IsFull() {
		return tr_count == number_of_trucks;
	}

	bool IsEmpty() {
		return tr_count == 0;
	}

	bool HasAny() {
		return tr_count > 0;
	}
};

LoadingQueue lq;
WeightingQueue wq;

class Loader{
public:
	loader_number id;
	Truck current_truck;
	bool state;
	int cumulativ_working_time;
	int entering_time;
	int leaving_time;
	Loader()
	{
		state = false;
		cumulativ_working_time = 0;
		entering_time = 0;
		current_truck = Truck();
		leaving_time = 0;
	}

	void InitLoader(loader_number id) {
		this->id = id;
	}

	Loader operator=(Loader loader) {
		id = loader.id;
		state = loader.state;
		cumulativ_working_time = loader.cumulativ_working_time;
		entering_time = loader.entering_time;
		current_truck = loader.current_truck;

		return *this;
	}

	void SetCumulativ(int gc) {
		
	}

	int GetCumulativ() {
		return leaving_time - entering_time;
	}

	int GetCumulativTimed(int gc) {
		return (leaving_time - entering_time) - (leaving_time - gc);
	}
};

class Loaders {
public:
	int loader_count;
	Loader* loaders;
	int truck_count;
	int total_cumulativ_working_time;
	int last_loader_count;
	int last_mesurement;

	Loaders(int loader_count = number_of_loaders)
	{
		this->loader_count = loader_count;
		loaders = new Loader[loader_count];
		truck_count = 0;
		total_cumulativ_working_time = 0;
		lq = LoadingQueue();
		last_loader_count = 0;
		last_mesurement = 0;
		InitLoaders();
	}

	void InitLoaders() {
		if (loader_count == 3) {
			loaders[0].InitLoader(LDR1);
			loaders[1].InitLoader(LDR2);
			loaders[2].InitLoader(LDR3);
		}
	}

	int GetCurrentTruckCount() {
		truck_count = 0;
		for (int i = 0; i < loader_count; i++)
		{
			if(loaders[i].state)
				truck_count++;
		}

		return truck_count;
	}

	void Start_Loading(Truck tr,int gc = global_clock) {
		for (int i = 0; i < loader_count; i++)
		{
			if (!loaders[i].state) {

				loaders[i].state = true;
				loaders[i].current_truck = tr;
				loaders[i].entering_time = gc;
				loaders[i].leaving_time = gc + round(tr.CurrentLoading());
				last_loader_count++;
				printf("\x1B[32m\n\n Truck ");
				printf("%d", tr.id);
				printf(" has started loading at ");
				printf("%d", gc);
				printf(" minutes.");

				return;
			}
		}

		printf("All loaders are bussy currently.");
	}

	void FinishLoading(Truck tr, int gc = global_clock) {
		for (int i = 0; i < loader_count; i++)
		{
			if (loaders[i].state) {
				if (loaders[i].current_truck.id == tr.id) {

					total_cumulativ_working_time += (gc- last_mesurement)*last_loader_count;
					


					Truck truck = loaders[i].current_truck;
					wq.Enqueue(truck);


					loaders[i].current_truck = Truck();
					loaders[i].entering_time = 0;
					loaders[i].state = false;
					last_mesurement = gc;
					last_loader_count--;

					if (lq.tr_count > 0) {
						truck = lq.Dequeue();
						this->Start_Loading(truck);
					}

					printf("\x1B[31m\n\n Truck ");
					printf("%d", tr.id);
					printf(" has finished loading at ");
					printf("%d", gc);
					printf(" minutes.");
					
					return;
				}
			}
		}

		printf("All loaders are empty currently or truck is not being loaded currently.");
	}

	void CheckEvents(int gc = global_clock) {
		for (int i = 0; i < loader_count; i++)
		{
			if (loaders[i].state) {
				if (loaders[i].leaving_time == gc) {
					FinishLoading(loaders[i].current_truck);
				}
			}
		}
	}

	int GetNumberOfBussyLoaders() {
		int c = 0;
		for (int i = 0; i < number_of_loaders; i++)
		{
			if(loaders[i].state && !loaders[i].current_truck.id == TR_DOESNT_EXIST)
				c++;
		}
		return c;
	}

	void BeginWork() {
		Truck tr1 = lq.Dequeue();
		Truck tr2 = lq.Dequeue();
		Truck tr3 = lq.Dequeue();

		this->Start_Loading(tr1);
		this->Start_Loading(tr2);
		this->Start_Loading(tr3);
	}

};

class Weighter {
public:
	weighter_number id;
	Truck current_truck;
	bool state;
	int cumulativ_working_time;
	int entering_time;

	Weighter()
	{
		state = false;
		cumulativ_loading_time = 0;
		entering_time = 0;
		current_truck = Truck();
	}

	void InitWeighter(weighter_number id) {
		this->id = id;
	}

	Weighter operator=(Weighter loader) {
		id = loader.id;
		state = loader.state;
		cumulativ_working_time = loader.cumulativ_working_time;
		entering_time = loader.entering_time;
		current_truck = loader.current_truck;

		return *this;
	}
};

class Weighters{
public:
	int weighter_count;
	Weighter* weighters;
	int truck_count;
	int total_cumulativ_working_time;
	int last_loader_count;
	int last_mesurement;

	Weighters(int weighter_count = number_of_weighters)
	{
		this->weighter_count = weighter_count;
		weighters = new Weighter[weighter_count];
		truck_count = 0;
		total_cumulativ_working_time = 0;
		last_loader_count = 0;
		last_mesurement = 0;
		InitWeighters();
	}

	void InitWeighters() {
		if (weighter_count == 2) {
			weighters[0].InitWeighter(WGHTR1);
			weighters[1].InitWeighter(WGHTR2);
		}
	}

	int GetCurrentTruckCount() {
		truck_count = 0;
		for (int i = 0; i < weighter_count; i++)
		{
			if (weighters[i].state)
				truck_count++;
		}

		return truck_count;
	}

	void Start_Weighting(Truck tr, int gc = global_clock) {
		for (int i = 0; i < weighter_count; i++)
		{
			if (!weighters[i].state) {

				total_cumulativ_working_time += last_loader_count * (gc - last_mesurement);

				weighters[i].state = true;
				weighters[i].current_truck = tr;
				weighters[i].entering_time = gc;
				last_loader_count++;
				last_mesurement = gc;

				printf("\x1B[32m\n\n Truck ");
				printf("%d", tr.id);
				printf(" has started weighting at ");
				printf("%d", gc);
				printf(" minutes.");

				return;
			}
		}

		printf("All loaders are bussy currently.");
	}

	void FinishWeighting(Truck tr, int gc = global_clock) {
		for (int i = 0; i < weighter_count; i++)
		{
			if (weighters[i].state) {
				if (weighters[i].current_truck.id == tr.id) {

					printf("\x1B[31m\n\n Truck ");
					printf("%d", tr.id);
					printf(" has finished weighting at ");
					printf("%d", gc);
					printf(" minutes.");

					total_cumulativ_working_time += (gc - last_mesurement) * last_loader_count;

					weighters[i].current_truck = Truck();
					weighters[i].entering_time = 0;
					weighters[i].state = false;
					last_mesurement = gc;
					last_loader_count--;

					if (wq.tr_count > 0) {
						tr = wq.Dequeue();
						this->Start_Weighting(tr);
					}

					return;
				}
			}
		}

		printf("All weighters are empty currently or truck is not being loaded currently.");
	}

	void CheckEvents(int gc = global_clock) {
		for (int i = 0; i < weighter_count; i++)
		{
			if (weighters[i].state) {
				if (round(weighters[i].current_truck.CurrentWeighting()) == gc - weighters[i].entering_time) {
					FinishWeighting(weighters[i].current_truck);
				}
			}
		}
	}

	int GetNumberOfBussyWighters() {
		int c = 0;
		for (int i = 0; i < number_of_loaders; i++)
		{
			if (weighters[i].state && !weighters[i].current_truck.id == TR_DOESNT_EXIST)
				c++;
		}
		return c;
	}
};

//Simulation
class Simulation {
public:

	Truck* trucks;

	//Loading Components
	Loaders loaders;

	//Loading data
	int cumulativ_loading_time;
	float* loading_series;

	//Weighting components
	Weighters weighters;

	//Weighting data
	int cumulativ_weighting_time;
	float* weighting_series;

	//Traveling
	float* traveling_series;

	void PrintTimeSeriesData() {
		printf("\nWeibull by inverse transformation technique for travel time: \n[ ");
		for (int i = 0; i < number_of_trucks; i++)
		{
			printf("%.5f", traveling_series[i]);
			if (i != number_of_trucks - 1)
				printf(" , ");
			else
				printf(" ]");
		}
		printf("\n");

		printf("\nUnifrom by inverse transformation technique for loading time: \n[ ");
		for (int i = 0; i < number_of_trucks; i++)
		{
			printf("%.5f", loading_series[i]);
			if (i != number_of_trucks - 1)
				printf(" , ");
			else
				printf(" ]");
		}
		printf("\n");

		printf("\nUnifrom by inverse transformation technique for weighting time : \n[ ");
		for (int i = 0; i < number_of_trucks; i++)
		{
			printf("%.5f", weighting_series[i]);
			if (i != number_of_trucks - 1)
				printf(" , ");
			else
				printf(" ]");
		}
		printf("\n");
	}

	Simulation(float* seed1, float* seed2)
	{
		cumulativ_loading_time = 0;
		cumulativ_weighting_time = 0;

		loading_series = new float[8];
		traveling_series = new float[8];
		weighting_series = new float[8];

		loaders = Loaders();

		weighters = Weighters();
		wq = WeightingQueue();

		trucks = new Truck[8];

		GenerateRandomVariates(seed1, seed2);

		printf("--------------- Generated Radnom Time Series Data ---------------------\n");
		PrintTimeSeriesData();

		InitTrucks();
	}

	void GenerateRandomVariates(float*seed1, float* seed2) {
		loading_series = RandVariateGenerator::Generate_Uniforme_Varaiates(10, 20, seed1, number_of_trucks);
		weighting_series = RandVariateGenerator::Generate_Uniforme_Varaiates(5.60, 10, seed2, number_of_trucks);
		traveling_series = RandVariateGenerator::Generate_Weibull_Varaiates(30, 35, seed2, number_of_trucks);
	}

	void InitTrucks() {

		printf("\x1B[33m\n-------------Intial data of trucks -------------\n\n");
		for (int i = 0; i < number_of_trucks; i++)
		{
			trucks[i].InitTruck((truck_numbers)(i+1), (int)round(loading_series[i]), (int)round(weighting_series[i]), (int)round(traveling_series[i]),LQ,1);

			lq.Enqueue(trucks[i]);

			trucks[i].Print(); // Printing details of trucks
		}
	}

	void StartSimulation(int duration = 55) {

		printf("\x1B[33m\n\n ------------------Simulation has started-----------------\033[0m\t\t");
		printf("\x1B[33m\n\n ------------------You can view the events bellow-----------------\033[0m\t\t");

		loaders.BeginWork();

		for (global_clock; global_clock <= duration; global_clock++)
		{
			loaders.CheckEvents(global_clock);
			weighters.CheckEvents(global_clock);
			if (wq.HasAny() && weighters.GetNumberOfBussyWighters() < 2) {
				Truck tr = wq.Dequeue();
				weighters.Start_Weighting(tr);
			}

			cumulativ_loading_time = loaders.total_cumulativ_working_time;
			cumulativ_weighting_time = weighters.total_cumulativ_working_time;
		}
	};

	void GetReport(int duration) {
		cumulativ_loading_time = loaders.total_cumulativ_working_time;
		cumulativ_weighting_time = weighters.total_cumulativ_working_time;
		printf("\x1B[33m\n\n----------------- Report -------------------\033[0m\t\t");
		printf("\x1B[32m\n\nCumulativ loading time -> ");
		printf("%d", cumulativ_loading_time);

		printf("\n\nCumulativ weighting time -> ");
		printf("%d", cumulativ_weighting_time);

		printf("\x1B[33m\n\n---------------------------------------------\033[0m\t\t");


		float luk = (cumulativ_loading_time / number_of_loaders);
		float wuk = (cumulativ_weighting_time / number_of_weighters);

		printf("\x1B[32m\n\nCoeficient of utilization of weighters -> ");
		printf("%.4f", wuk/duration);

		printf("\n\nCoeficient of utilization of loaders -> ");
		printf("%.4f", luk/duration);

		printf("\x1B[33m\n\n---------------------------------------------\033[0m\t\t");

		float avg = 0;
		float var = 0;
		float std_dev = 0;


		for (int i = 0; i < number_of_trucks; i++)
		{
			avg += loading_series[i];
		}

		avg = avg / number_of_trucks;

		printf("\x1B[32m\n\nLoading time : ");


		printf("\n\nMean -> ");
		printf("%.4f", avg);

		for (int i = 0; i < number_of_trucks; i++)
		{
			var += pow(loading_series[i] - avg, 2);
		}

		var /= number_of_trucks;

		printf("\n\nVariance -> ");
		printf("%.4f", var);

		std_dev = sqrt(var);

		printf("\n\nStd. Dev. -> ");
		printf("%.4f", std_dev);

		//

		avg = 0;

		for (int i = 0; i < number_of_trucks; i++)
		{
			avg += weighting_series[i];
		}

		avg = avg / number_of_trucks;

		printf("\x1B[33m\n\n---------------------------------------------\033[0m\t\t");


		printf("\x1B[32m\n\nWeighting time : ");
		printf("\n\n\Mean -> ");
		printf("%.4f", avg);

		for (int i = 0; i < number_of_trucks; i++)
		{
			var += pow(weighting_series[i] - avg,2);
		}

		var /= number_of_trucks;

		printf("\n\nVariance -> ");
		printf("%.4f", var);

		std_dev = sqrt(var);

		printf("\n\nStd. Dev. -> ");
		printf("%.4f", std_dev);

		printf("\x1B[33m\n\n---------------------------------------------\033[0m\t\t");


		avg = 0;

		for (int i = 0; i < number_of_trucks; i++)
		{
			avg += traveling_series[i];
		}

		avg = avg / number_of_trucks;

		printf("\x1B[32m\n\Traveling time : ");
		printf("\n\nMean -> ");
		printf("%.4f", avg);

		for (int i = 0; i < number_of_trucks; i++)
		{
			var += pow(traveling_series[i] - avg, 2);
		}

		var /= number_of_trucks;

		printf("\n\nVariance -> ");
		printf("%.4f", var);

		std_dev = sqrt(var);

		printf("\n\nStd. Dev. -> ");
		printf("%.4f", std_dev);


		printf("\n\n\033[0m\t\t");
	};

};

class Report {
public:
	int cumulative_loading_time;
	int cumulative_weighting_time;
	int cumulative_traveling_time;

	Report() {
		cumulative_loading_time = 0;
		cumulative_weighting_time = 0;
		cumulative_traveling_time = 0;
	}

	void AddLoadingTime(int time) {
		cumulative_loading_time += time;
	}
};

//Main function that runs the simulation
int main() {

	//Seed data used for random variate genereating
	float arr_1[] = { 0.1306, 0.0422, 0.6597, 0.7965, 0.7696, 0.7791, 0.9211, 0.1862 };
	float arr_2[] = { 0.4357, 0.4146, 0.8353, 0.9953, 0.8004, 0.2892, 0.6533, 0.2398 };

	Simulation dump_truck_problem = Simulation(arr_1, arr_2);
	
	dump_truck_problem.StartSimulation();

	dump_truck_problem.GetReport(55);
	
}
