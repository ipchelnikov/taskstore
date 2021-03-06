//#include<bits/stdc++.h>
#include <map>
#include <iostream>
#include <fstream>
#include <chrono>
//#include <ctime>

using namespace std;

// https://www.hackerrank.com/challenges/attending-workshops/copy-from/81184701

//Define the structs Workshops and Available_Workshops.
//Implement the functions initialize and CalculateMaxWorkshops

struct Available_Workshops
{
    void insert(int end_time, int start_time){
        m_end_time.insert(std::make_pair(end_time, start_time));
        m_start_time.insert(std::make_pair(start_time, end_time));
    }
        
    std::multimap<int, int> m_end_time;
    std::multimap<int, int> m_start_time;
};

int CalculateMaxWorkshops(Available_Workshops* av_workshops)
{
    int count = 0;
    
    while(true)
    {
            count++;
        
            std::multimap<int, int>::iterator i = av_workshops->m_end_time.begin();

            int start_t = i->second;
            int end_t = i->first;

            auto j = av_workshops->m_start_time.find(start_t);

            while(j->second != end_t)
                j++;

            av_workshops->m_end_time.erase(i);
            av_workshops->m_start_time.erase(j);

            if(av_workshops->m_end_time.empty())
                return count;

            // Remove items from start map, starting before the cuurent workshop end
            i = av_workshops->m_start_time.begin();

            while(i->first < end_t)
            {
                auto j = av_workshops->m_end_time.find(i->second);

                while(j->second != i->first)
                    j++;

                av_workshops->m_end_time.erase(j);
                i = av_workshops->m_start_time.erase(i);

                if(av_workshops->m_end_time.empty())
                    return count;
            }
    }
    
    return 0;
}

static Available_Workshops* initialize(int* start_time, int* duration, int n)
{
    Available_Workshops* av = new Available_Workshops;
    
    for(int i = 0 ; i < n; i++)
        av->insert((start_time[i]+duration[i]), start_time[i]);
        
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
