#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

// Task description: https://codeforces.com/gym/102558/problem/C

constexpr auto MAX_DELTA = 10'000'000'000ul;

void run_test()
{
    int num;
    std::cin >> num;

    std::vector<unsigned long> v;
    v.reserve(num);

    for( auto i = 0; i < num; ++i )
    {
        unsigned long a;
        std::cin >> a;
        v.push_back(a);
    }

    unsigned long min_delta = MAX_DELTA;

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
        run_test();
}
