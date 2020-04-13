#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
 
void test()
{
    int num;
    std::cin >> num;
 
    std::vector<int> v;
 
    for( auto i = 0; i < num; ++i )
    {
        int a;
        std::cin >> a;
        v.push_back(a);
    }
 
    int min_delta = 10000000;
 
    std::sort(v.begin(), v.end());
 
    for( auto val = v.begin(); val != v.end()-1; ++val )
        min_delta = std::min(min_delta, *val^*(val+1) );
 
    std::cout << min_delta << '\n';
}
 
 
int main()
{
    int num_of_tests = 0;
    std::cin >> num_of_tests;
 
    for(auto i = 0; i < num_of_tests; ++i)
    {
        test();
    }
}
