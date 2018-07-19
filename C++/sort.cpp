#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include <unordered_set>

template<class T>
typename std::enable_if<
	std::is_base_of<std::random_access_iterator_tag,
	typename std::iterator_traits<typename T::iterator>::iterator_category>::value, void>::type
mysort(T& t) {
	std::sort(t.begin(), t.end());
}

template<class T>
typename std::enable_if<
	!std::is_base_of<std::random_access_iterator_tag,
	typename std::iterator_traits<typename T::iterator>::iterator_category>::value, void>::type
mysort(T& t) {
	t.sort();
}

template<typename T>
void myprint(T& t) {
	for(auto i : t)
		std::cout << i << " ";

	std::cout << std::endl;
}


int main()
{
	std::string s = "This is string!";
	std::list<std::string> ls = {"This", "is", "string", "And"};
	std::vector<std::string> vs = {"This", "is", "string", "And"};

	mysort(s);
	mysort(ls);
	mysort(vs);

	myprint(s);
	myprint(ls);
	myprint(vs);

	return 0;
}
