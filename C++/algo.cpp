#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <list>

template<typename T>
using Iterator = typename T::iterator;
template<typename C, typename V>
std::vector<Iterator<C>> find_all(C& s, V value) {
	std::vector<Iterator<C>> v;
	
	Iterator<C> it = s.begin();

	while((it = std::find(it, s.end(), value)) != s.end())
		v.push_back(it++);

	return v;
}

int main()
{
	std::string s = "This is string!";

	for(auto i : find_all(s, 's'))
		std::cout << *i << std::endl;

	std::list<std::string> ls = {"This", "is", "string"};

	for(auto i : find_all(ls, "is"))
		std::cout << *i << std::endl;

	std::vector<std::string> vs = {"This", "is", "string"};

	for(auto i : find_all(ls, "string"))
		std::cout << *i << std::endl;

	return 0;
}
