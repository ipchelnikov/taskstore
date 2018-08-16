///////////////////////////////////////////////////////////////////////////////
//
// https://www.hackerrank.com/challenges/attending-workshops/copy-from/81184701
//
// Define the structs Workshops and Available_Workshops.
// Implement the functions initialize and CalculateMaxWorkshops
//

#include <fstream>
#include <iostream>
#include <chrono>
#include <map>

struct Available_Workshops
{
    Available_Workshops(int* start_time, int* duration, int n) {
        for(int i =0; i < n; ++i)
            schedule.insert(std::make_pair(start_time[i]+duration[i], start_time[i]));
    }
    
    int CalculateMaxWorkshops()
    {
        int count = 0;
        int current_end = 0;

        for(auto i : schedule)
        {
           if(i.second >= current_end)
           {
               count++;
	       current_end = i.first;
	}
    }

    std::multimap<int, int> schedule;
};

int main(int argc, char *argv[]) {

    int n; // number of workshops
    int* start_time = new int[n];
    int* duration = new int[n];

    // Read rest data
    std::ifstream ifst("workshop_test.txt");

    ifst >> n;
    for(int i=0; i < n; i++)
        ifst >> start_time[i];

    for(int i = 0; i < n; i++)
        ifst >> duration[i];

    // Initialization section
    auto start = std::chrono::system_clock::now();
    Available_Workshops av(start_time,duration, n);
    auto end = std::chrono::system_clock::now();
    std::cout << "Initialization time = " << std::chrono::duration<double>(end-start).count() << "\n";
    
    // Calculation section
    start = std::chrono::system_clock::now();    
    std::cout << av.CalculateMaxWorkshops() << std::endl;
    end = std::chrono::system_clock::now();
    std::cout << "Calculation time = " << std::chrono::duration<double>(end-start).count() << "\n";
    
    return 0;
}
