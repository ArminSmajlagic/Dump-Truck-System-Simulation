//#include <iostream>;
//#include "RandomVariateGenerating.h"
//
////Enumeration that help with tracking different components of simulation
//enum location {
//	LOADER = 1,
//	WEIGHTER = 2,
//	ROAD = 3,
//	LQ = 4,
//	WQ = 5
//};
//
//enum truck_numbers {
//	TR_DOESNT_EXIST = 0,
//	TR1 = 1,
//	TR2 = 2,
//	TR3 = 3,
//	TR4 = 4,
//	TR5 = 5,
//	TR6 = 6,
//	TR7 = 7,
//	TR8 = 8,
//};
//
//enum loader_number {
//	LDR1 = 1,
//	LDR2 = 2,
//	LDR3 = 3
//};
//
//enum weighter_number
//{
//	WGHTR1 = 1,
//	WGHTR2 = 2,
//};
//
//// Components of the simulation
//
//class Truck {
//public:
//	int current_iteration;
//	truck_numbers tr_num;
//	location current_location;
//	int* loading_times;
//	int* weighting_times;
//	int* traveling_times;
//
//	//Possible extensions
//	int cumulativ_working_time;
//
//	Truck()
//	{
//
//	}
//
//	location get_current_location() {
//		return current_location;
//	}
//
//	int get_current_loading_time() {
//		return loading_times[current_iteration-1];
//	}
//
//	void IncrementIteration() {
//		current_iteration++;
//	}
//
//	int get_current_weighting_time() {
//		return weighting_times[current_iteration - 1];
//	}
//
//	int get_current_traveling_time() {
//		return traveling_times[current_iteration - 1];
//	}
//
//	void InitTruck(truck_numbers tr_num, float loading_time, float weighting_time, float traveling_time){
//		this->tr_num = tr_num;
//		current_location = LQ;
//		current_iteration = 1;
//
//		loading_times = new int[10];
//		weighting_times = new int[10];
//		traveling_times = new int[10];
//
//		loading_times[0] = loading_time;
//		weighting_times[0] = weighting_time;
//		traveling_times[0] = traveling_time;
//	}
//
//	void AddTimeSeriesData(float loading_time, float weighting_time,float traveling_time) {
//		current_iteration++;
//		loading_times[current_iteration-1] = loading_time;
//		weighting_times[current_iteration - 1] = weighting_time;
//		traveling_times[current_iteration - 1] = traveling_time;
//	}
//
//	truck_numbers GetTruckNumber() {
//		return tr_num;
//	}
//
//	void SetTruckLocation(location tr_loc) {
//		current_location = tr_loc;
//	}
//};
//
//class Loader {
//public:
//	loader_number ldr_num; // Loader identifier
//	Truck current_holding_truck; // Current truck being loaded
//	bool state; // State is idle by default (state = false)
//	int cumulativ_loading_clock; // Cumulativ time of loader being bussy
//	int entering_time;
//	Loader() {
//
//	}
//
//	void InitLoader(loader_number ldr_num) {
//		entering_time = 0;
//		this->ldr_num = ldr_num;
//		state = false;
//		cumulativ_loading_clock = 0;
//	}
//
//	void StardLoading(Truck truck, int clock) {
//		state = true;
//		this->entering_time = clock;
//		current_holding_truck = truck;
//	}
//
//	Truck FinishLoading() {
//		Truck result = current_holding_truck;
//
//		cumulativ_loading_clock += result.get_current_loading_time();
//
//		current_holding_truck = Truck();
//
//		current_holding_truck.InitTruck(TR_DOESNT_EXIST,0,0,0);
//
//		return result;
//	}
//
//	int GetCumulativLoadingTime() {
//		return cumulativ_loading_clock;
//	}
//
//	bool GetState() {
//		return state;
//	}
//
//	Truck GetCurrentLoadingTruck() {
//		return current_holding_truck;
//	}
//
//	void SetCumulativLoadingClock(int value) {
//		cumulativ_loading_clock = value;
//	}
//};
//
//class Weighter {
//public:
//	weighter_number wghtr_num; // Weighter identifier
//	Truck current_holding_truck; // Current truck being weighted
//	bool state; // State is idle by default (state = false)
//	int cumulativ_weighting_clock; // Cumulativ time of weighter being bussy
//	int entering_time;
//	Weighter(){
//
//	}
//
//	void InitWeighter(weighter_number wghtr_num) {
//		this->wghtr_num = wghtr_num;
//		state = false;
//		cumulativ_weighting_clock = 0;
//	}
//
//	void StartWeighting(Truck truck, int clock) {
//		state = true;
//		entering_time = clock;
//		current_holding_truck = truck;
//	}
//
//
//	Truck FinishWeighting() {
//		Truck result = current_holding_truck;
//
//		cumulativ_weighting_clock += result.get_current_loading_time();
//
//		current_holding_truck = Truck();
//
//		current_holding_truck.InitTruck(TR_DOESNT_EXIST, 0, 0, 0);
//
//		return result;
//	}
//
//	int GetCumulativWeightingTime() {
//		return cumulativ_weighting_clock;
//	}
//
//	bool GetState() {
//		return state;
//	}
//
//	Truck GetCurrentWeightingTrucks() {
//		return current_holding_truck;
//	}
//
//	void SetCumulativWeightingClock(int value) {
//		cumulativ_weighting_clock = value;
//	}
//};
//
////FIFO Loading Queue Data Structure
//class LoadingQueue{
//public:
//	Truck* trucks;
//	int num_of_trucks;
//	int size;
//
//	LoadingQueue() {
//		size = 10;
//		trucks = new Truck[size];
//		num_of_trucks = 0;
//	}
//
//	void EnqueueTruck(Truck truck) {
//		trucks[num_of_trucks++] = truck;
//
//		if (IsFull())
//			ExpandQueue();
//	}
//
//	Truck DequeueTruck() {
//		if (!IsEmpty()) {
//			Truck result = trucks[0];
//
//			for (int i = 0; i < num_of_trucks - 1; i++)
//			{
//				trucks[i] = trucks[i + 1];
//			}
//
//			return result;
//		}
//		else
//			printf("\nError: Sorry but the WQ is empty.\n");
//
//	}
//
//	bool IsFull() {
//		return num_of_trucks == size;
//	}
//
//	bool IsEmpty() {
//		return num_of_trucks == 0;
//	}
//
//	void ExpandQueue() {
//		size *= 2;
//
//		Truck* temp = new Truck[size];
//
//		for (int i = 0; i < size / 2; i++)
//		{
//			temp[i] = trucks[i];
//		}
//
//		delete trucks;
//		trucks = nullptr;
//
//		trucks = temp;
//	}
//
//	int GetCurrentNumberOfTrucks()
//	{
//		return num_of_trucks;
//	}
//};
//
////FIFO Weighting Queue Data Structure
//class WeightingQueue {
//public:
//	Truck* trucks;
//	int num_of_trucks;
//	int size;
//	WeightingQueue() {
//		size = 10;
//		trucks = new Truck[size];
//		num_of_trucks = 0;
//	}
//
//	void EnqueueTruck(Truck truck) {
//		trucks[num_of_trucks++] = truck;
//
//		if (IsFull())
//			ExpandQueue();
//	}
//
//	Truck DequeueTruck() {
//		if (!IsEmpty()) {
//			Truck result = trucks[0];
//
//			for (int i = 0; i < num_of_trucks-1; i++)
//			{
//				trucks[i] = trucks[i + 1];
//			}
//
//			return result;
//		}
//		else
//			printf("\nError: Sorry but the WQ is empty.\n");
//
//	}
//
//	bool IsFull() {
//		return num_of_trucks == size;
//	}
//
//	bool IsEmpty() {
//		return num_of_trucks == 0;
//	}
//
//	void ExpandQueue() {
//		size *= 2;
//
//		Truck* temp = new Truck[size];
//
//		for (int i = 0; i < size/2; i++)
//		{
//			temp[i] = trucks[i];
//		}
//
//		delete trucks;
//		trucks = nullptr;
//
//		trucks = temp;	
//	}
//
//	int GetCurrentNumberOfTrucks() 
//	{ 
//		return num_of_trucks;
//	}
//
//};
//
////Result of simulation should yield results in the following report
//
//class Report {
//	float loader_utilization_koef;
//	float weighter_utilization_koef;
//
//public:
//
//	Report(float luk, float wuk)
//	{
//		loader_utilization_koef = luk;
//		weighter_utilization_koef = wuk;
//	}
//
//	void Print_Report(float luk,float wuk) {
//
//		printf("\nLoading utilization coefficient :");
//		printf("%.5f", luk);
//		printf("\Weighting utilization coefficient :");
//		printf("%.5f", wuk);
//	}
//};
//
//class Travels {
//public:
//	Truck* currently_traveling_trucks;
//	int* traveling_cumulativ;
//	int num_of_trucks_traveling;
//	int max_trucks = 8;
//
//	int cumulativ_time;
//	Travels()
//	{
//		cumulativ_time = 0;
//		num_of_trucks_traveling = 0; 
//		max_trucks = 8; //This is the max value that it can reach
//		currently_traveling_trucks = new Truck[max_trucks];
//		traveling_cumulativ = new int[max_trucks];
//
//		for (int i = 0; i < max_trucks; i++)
//		{
//			traveling_cumulativ[i] = 0;
//			currently_traveling_trucks[i] = Truck();
//			currently_traveling_trucks[i].InitTruck(TR_DOESNT_EXIST,0,0,0);
//		}
//	}
//
//	void CheckTrucks(Truck truck, int current_time) {
//
//		for (int i = 0; i < max_trucks; i++)
//		{
//			if (!currently_traveling_trucks[i].GetTruckNumber() == TR_DOESNT_EXIST) {
//				if (currently_traveling_trucks[i].get_current_traveling_time() == current_time) {// If current truck is finished traveling 
//					//Calculating the time
//					cumulativ_time += currently_traveling_trucks[i].get_current_traveling_time();
//					currently_traveling_trucks[i].IncrementIteration(); //incrementing iteration of simulation (1 cycle duration = LQT, LT, WQT, WT, T))
//				}
//			}
//		}
//
//	}
//
//	void AddTruck(Truck truck) {
//		currently_traveling_trucks[num_of_trucks_traveling] = truck;
//	}
//
//	void RemoveTruck() {
//
//	}
//};
//
////Simulation
//
//class Simulation {
//public:
//
//	// Initial data
//	int no_of_trucks = 8;
//	int no_of_loaders = 3;
//	int no_of_weighters = 2;
//
//	// Simulation components
//	Truck* trucks;
//	Loader* loaders;
//	Weighter* weighters;
//	LoadingQueue loading_queue;
//	WeightingQueue weighting_queue;
//
//	//Messurements of time
//	int global_simulation_clock;
//	int total_cumulativ_loading_clock;
//	int total_cumulativ_weighting_clock;
//
//	//Randomly generated data (used for simulating passage of time)
//	float* loading_time_series;
//	float* weighting_time_series;
//	float* traveling_time_series;
//
//	//Helper seed data for random variate generating
//	float* seed_data_1;
//	float* seed_data_2;
//
//	//Counters
//	int current_loading_point = 0;
//	int current_weghting_point = 0;
//	int current_traveling_point = 0;
//
//	void PrepareLoadersAndWeighters() {
//		for (int i = 0; i < no_of_loaders; i++)
//		{
//			loaders[i].InitLoader((loader_number)(i + 1));
//		}
//
//		for (int i = 0; i < no_of_weighters; i++)
//		{
//			weighters[i].InitWeighter((weighter_number)(i + 1));
//		}
//	}
//
//	void PrepareTrucks() {
//
//		GetSeedData();
//
//		GetTimeSeriesData();
//
//		for (int i = 0; i < no_of_trucks; i++)
//		{
// 
//			trucks[i].InitTruck((truck_numbers)(i + 1), round(loading_time_series[i]), round(weighting_time_series[i]), round(traveling_time_series[i]));
//
//			loading_queue.EnqueueTruck(trucks[i]);
//		}
//	}
//
//	void GetSeedData() {
//		float arr_1[] = { 0.1306, 0.0422, 0.6597, 0.7965, 0.7696, 0.7791, 0.9211, 0.1862 };
//		float arr_2[] = { 0.4357, 0.4146, 0.8353, 0.9953, 0.8004, 0.2892, 0.6533, 0.2398 };
//
//		//	float R1[] = { 0.1306, 0.0422, 0.6597, 0.7965, 0.7696, 0.7791, 0.9211, 0.1862};
////
////	float R2[] = { 0.4357, 0.4146, 0.8353, 0.9953, 0.8004, 0.2892, 0.6533, 0.2398};
//		seed_data_1 = new float[no_of_trucks];
//		seed_data_2 = new float[no_of_trucks];
//
//		for (int i = 0; i < no_of_trucks; i++)
//		{
//			seed_data_1[i] = arr_1[i];
//			seed_data_2[i] = arr_2[i];
//		}
//	}
//
//	void GetTimeSeriesData() {
//		loading_time_series = RandVariateGenerator::Generate_Uniforme_Varaiates(10, 20, seed_data_1, no_of_trucks);
//			
//		weighting_time_series = RandVariateGenerator::Generate_Uniforme_Varaiates(5.60, 10, seed_data_2, no_of_trucks);
//		traveling_time_series = RandVariateGenerator::Generate_Weibull_Varaiates(30, 35, seed_data_2, no_of_trucks);
//	}
//
//
//	Simulation(int clock = 0)
//	{
//		
//		this->global_simulation_clock = clock;
//
//		trucks = new Truck[no_of_trucks];
//		loaders = new Loader[no_of_loaders];
//		weighters = new Weighter[no_of_loaders];
//
//		loading_queue = LoadingQueue();
//		weighting_queue = WeightingQueue();
//
//		PrepareLoadersAndWeighters();
//
//		PrepareTrucks();
//	}
//
//	//Left to correctly calculate cumulatives for loaders and weighters (helper -> remembering  the time that the truck went in to loader or weighter)
//	//Handle traveling time appropriately
//
//	void StartSimulation(int duration_of_simulation, int clock = 0, float* seed_data_1 = NULL, float* seed_data_2 = NULL) {
//		
//		total_cumulativ_loading_clock = 0;
//		int last_saved_value_weighter = 0;
//		int last_saved_value_loader = 0;
//		int gsc = global_simulation_clock;
//		int sim_dur = duration_of_simulation;
//		for (global_simulation_clock;  global_simulation_clock < sim_dur; )
//		{
//			if (global_simulation_clock == 7) {
//				gsc = 7;
//			}
//
//			for (int i = 0; i < no_of_trucks; i++)
//			{
//				if (trucks[i].get_current_location() == 4 || trucks[i].get_current_location() == 1) { //If the current truck is waiting in queue to be loaded or is in loader
//					for (int l = 0; l < no_of_loaders; l++) // Checking every loader
//					{
//
//						if (trucks[i].get_current_location() == 4 || trucks[i].get_current_location() == 1) {
//							if (!loaders[l].GetState()) { //If loader is idle
//								Truck truck = loading_queue.DequeueTruck();	//Removing first truck from queue				
//								loaders[l].StardLoading(truck, global_simulation_clock); //Starting the loading of truck
//								//Remember the time it entered the queue
//							}
//							else { //If Loader is bussy
//								if (loaders[l].GetCurrentLoadingTruck().GetTruckNumber() == trucks[i].GetTruckNumber()) { //check if the current truck is being loaded at this loader
//									if (global_simulation_clock == trucks[i].get_current_loading_time()) { //Check if truck is finsihed loading
//										//Send truck to weighting queue
//										trucks[i].SetTruckLocation((location)5);
//										//Check where is the correct position for this calculation
//										loaders[0].SetCumulativLoadingClock(global_simulation_clock); //rethink this part
//										loaders[1].SetCumulativLoadingClock(global_simulation_clock); //rethink this part
//										loaders[2].SetCumulativLoadingClock(global_simulation_clock); //rethink this part
//
//										weighters[0].SetCumulativWeightingClock(global_simulation_clock); //rethink this part
//										weighters[1].SetCumulativWeightingClock(global_simulation_clock); //rethink this part
//										weighters[2].SetCumulativWeightingClock(global_simulation_clock); //rethink this part
//
//										if (loaders[0].GetState())
//											total_cumulativ_loading_clock += loaders[0].GetCumulativLoadingTime() - last_saved_value_loader;
//										if (loaders[1].GetState())
//											total_cumulativ_loading_clock += loaders[1].GetCumulativLoadingTime() - last_saved_value_loader;
//										if (loaders[2].GetState())
//											total_cumulativ_loading_clock += loaders[2].GetCumulativLoadingTime() - last_saved_value_loader;
//
//										if (weighters[0].GetState())
//											total_cumulativ_weighting_clock += weighters[0].GetCumulativWeightingTime() - last_saved_value_weighter;
//										if (weighters[1].GetState())
//											total_cumulativ_weighting_clock += weighters[1].GetCumulativWeightingTime() - last_saved_value_weighter;
//										if (weighters[2].GetState())
//											total_cumulativ_weighting_clock += weighters[2].GetCumulativWeightingTime() - last_saved_value_weighter;
//
//										last_saved_value_weighter = weighters[0].GetCumulativWeightingTime();
//										last_saved_value_loader = loaders[0].GetCumulativLoadingTime();
//										//Enqueu truck to WQ
//										weighting_queue.EnqueueTruck(trucks[i]);
//									}
//								}
//							}
//						}
//						
//					}
//				}
//				else if (trucks[i].get_current_location() == 2 || trucks[i].get_current_location() == 5) //Current truck is waiting to be weighted in queue or is being weighted currently
//				{
//					for (int w = 0; w < no_of_loaders; w++) // Checking every loader
//					{
//						if (!weighters[w].GetState()) { //If weighter is idle
//							Truck truck = weighting_queue.DequeueTruck();	//Removing first truck from queue				
//							weighters[w].StartWeighting(truck, global_simulation_clock); //Starting the loading of truck
//							//Remember the time it entered the queue
//						}
//						else { //If Loader is bussy
//							if (weighters[w].GetCurrentWeightingTrucks().GetTruckNumber() == trucks[i].GetTruckNumber()) { //check if the current truck is being loaded at this loader
//								if (global_simulation_clock == trucks[i].get_current_weighting_time()) { //Check if truck is finsihed loading
//									//Send truck to weighting queue
//									trucks[i].SetTruckLocation((location)3);
//									//Increase cumulative sum for loader
//									loaders[0].SetCumulativLoadingClock(global_simulation_clock); //rethink this part
//									loaders[1].SetCumulativLoadingClock(global_simulation_clock); //rethink this part
//									loaders[2].SetCumulativLoadingClock(global_simulation_clock); //rethink this part
//
//									weighters[0].SetCumulativWeightingClock(global_simulation_clock); //rethink this part
//									weighters[1].SetCumulativWeightingClock(global_simulation_clock); //rethink this part
//									weighters[2].SetCumulativWeightingClock(global_simulation_clock); //rethink this part
//
//									if (loaders[0].GetState())
//										total_cumulativ_loading_clock += loaders[0].GetCumulativLoadingTime() - last_saved_value_loader;
//									if (loaders[1].GetState())
//										total_cumulativ_loading_clock += loaders[1].GetCumulativLoadingTime() - last_saved_value_loader;
//									if (loaders[2].GetState())
//										total_cumulativ_loading_clock += loaders[2].GetCumulativLoadingTime() - last_saved_value_loader;
//
//									if (weighters[0].GetState())
//										total_cumulativ_weighting_clock += weighters[0].GetCumulativWeightingTime() - last_saved_value_weighter;
//									if (weighters[1].GetState())
//										total_cumulativ_weighting_clock += weighters[1].GetCumulativWeightingTime() - last_saved_value_weighter;
//									if (weighters[2].GetState())
//										total_cumulativ_weighting_clock += weighters[2].GetCumulativWeightingTime() - last_saved_value_weighter;
//
//									last_saved_value_weighter = weighters[0].GetCumulativWeightingTime();
//									last_saved_value_loader = loaders[0].GetCumulativLoadingTime();
//									
//								}
//							}
//						}
//					}
//				}
//				//else if (trucks[i].get_current_location() == 3) { // Check if current truck is traveling
//
//				//	//might need its own object for holding values
//				//	if (gsc == trucks[i].get_current_traveling_time()) {
//				//		//handle event
//				//	}
//				//}
//			}
//			global_simulation_clock++;
//		}
//	}
//
//	void GetResults() {
//
//		//calculate luk & wuk
//
//		float luk = (total_cumulativ_loading_clock / no_of_loaders) / global_simulation_clock;
//
//		float wuk = (total_cumulativ_weighting_clock / no_of_loaders) / global_simulation_clock;
//
//		//Construct a report
//
//		Report simulation_results = Report(luk, wuk);
//
//		// Print results
//
//		simulation_results.Print_Report(luk, wuk);
//	}
//
//	void PrintTimeSeriesData() {
//		printf("\nWeibull by inverse transformation technique for travel time: \n[ ");
//		for (int i = 0; i < no_of_trucks; i++)
//		{
//			printf("%.5f", traveling_time_series[i]);
//			if (i != no_of_trucks - 1)
//				printf(" , ");
//			else
//				printf(" ]");
//		}
//		printf("\n");
//
//		printf("\nUnifrom by inverse transformation technique for loading time: \n[ ");
//		for (int i = 0; i < no_of_trucks; i++)
//		{
//			printf("%.5f", loading_time_series[i]);
//			if (i != no_of_trucks - 1)
//				printf(" , ");
//			else
//				printf(" ]");
//		}
//		printf("\n");
//
//		printf("\nUnifrom by inverse transformation technique for weighting time : \n[ ");
//		for (int i = 0; i < no_of_trucks; i++)
//		{
//			printf("%.5f", weighting_time_series[i]);
//			if (i != no_of_trucks - 1)
//				printf(" , ");
//			else
//				printf(" ]");
//		}
//		printf("\n");
//	}
//};
//
////Siulation test
//
//void main() {
//
//	Simulation dump_truck_problem = Simulation();
//
//	//See the data that we work with
//
//	dump_truck_problem.PrintTimeSeriesData();
//
//	//Start the simulation
//
//	dump_truck_problem.StartSimulation(55);
//
//	//See the results of simulation (performance messurements)
//
//	dump_truck_problem.GetResults();
//}