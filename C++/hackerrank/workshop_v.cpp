//#include<bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <algorithm>

using namespace std;

// https://www.hackerrank.com/challenges/attending-workshops/copy-from/81184701

//Define the structs Workshops and Available_Workshops.
//Implement the functions initialize and CalculateMaxWorkshops

struct Available_Workshops
{

    struct time {
        int start_time;
        int end_time;
    };
    std::vector<time> v_time;
};

int CalculateMaxWorkshops(Available_Workshops* av)
{
    int count = 0;
    
    std::sort(av->v_time.begin(), av->v_time.end(), [](Available_Workshops::time a, Available_Workshops::time b){ return a.end_time < b.end_time;} );

    int current_end = 0;

    for(auto i : av->v_time)
    {
	if(i.start_time >= current_end)
	{
		count++;
		current_end = i.end_time;
	}
    }

    return count;
}

static Available_Workshops* initialize(int* start_time, int* duration, int n)
{
    Available_Workshops* av = new Available_Workshops;
    
    for(int i =0; i < n; ++i)
    {
        av->v_time.push_back(Available_Workshops::time{start_time[i], start_time[i]+duration[i]});
    }
        
    return av;
}

int main(int argc, char *argv[]) {
    std::ifstream ifst("workshop_test.txt");
    int n; // number of workshops
    ifst >> n;
    // create arrays of unknown size n
    int* start_time = new int[n];
    int* duration = new int[n];

    for(int i=0; i < n; i++){
        ifst >> start_time[i];
    }
    for(int i = 0; i < n; i++){
        ifst >> duration[i];
    }

    Available_Workshops * ptr;
    auto start = std::chrono::system_clock::now();
    ptr = initialize(start_time,duration, n);
    auto end = std::chrono::system_clock::now();
    std::cout << "Initialization time = " << std::chrono::duration<double>(end-start).count() << "\n";
    
    start = std::chrono::system_clock::now();    
    cout << CalculateMaxWorkshops(ptr) << endl;
    end = std::chrono::system_clock::now();
    std::cout << "Calculation time = " << std::chrono::duration<double>(end-start).count() << "\n";
    
    return 0;
}
