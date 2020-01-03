// Another nice exercise from hackerrank.com, which I took to warm up after the long christmas weekend
// https://www.hackerrank.com/challenges/cpp-variadics/problem

#include <iostream>
using namespace std;

template <bool digit>
int reversed_binary_value()
{
    //std::cout << " digit2 ========>" <<  (digit ? 1 : 0) << "\n";
    return digit ? 1 : 0;
}

template <bool digit, bool digit1, bool...digits>
int reversed_binary_value()
{
    //std::cout << " digit1 ========>" <<  (digit ? 1 : 0) << "\n";
    return (reversed_binary_value<digit1, digits...>() << 1) + digit;
}

template <int n, bool...digits>
struct CheckValues {
  	static void check(int x, int y)
  	{
    	CheckValues<n-1, 0, digits...>::check(x, y);
    	CheckValues<n-1, 1, digits...>::check(x, y);
  	}
};

template <bool...digits>
struct CheckValues<0, digits...> {
  	static void check(int x, int y)
  	{
    	int z = reversed_binary_value<digits...>();
    	std::cout << (z+64*y==x);
  	}
};

int main()
{
  	int t; std::cin >> t;

  	for (int i=0; i!=t; ++i) {
		int x, y;
    	cin >> x >> y;
    	CheckValues<6>::check(x, y);
    	cout << "\n";
  	}
}
