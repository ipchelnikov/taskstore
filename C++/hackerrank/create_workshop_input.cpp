#include <fstream>
#include <chrono>
#include <random>

int main()
{
	std::ofstream ost;
	ost.open("workshop_test.txt");

	const int n = 1000000;
	int start_t[n];	

	ost << n << std::endl;

	std::default_random_engine random_engine;
	std::uniform_int_distribution<int> distribution(0, n);

	for(int i = 0; i < n; ++i)
	{
		start_t[i] = distribution(random_engine);
		ost << start_t[i] << " ";
	}
	ost << std::endl;
	
	std::uniform_int_distribution<int> end_dst(1, 1000);
	for(int i = 0; i < n; ++i)
	{
		ost << end_dst(random_engine) << " ";
	}
	ost << std::endl;

	return 0;
}
