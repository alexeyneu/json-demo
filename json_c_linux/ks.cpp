#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>

int main()
{
	int m = 25;
	std::srand(time(NULL));
	std::vector <int> b(m);
	std::vector <int> c(m);
	std::generate (b.begin(), b.end() ,[]{ return  std::rand() % 9 + 1; });
	std::generate (c.begin(), c.end() ,[]{ return  std::rand() % 9 + 1; });
	b.erase(b.cend() - std::rand() % 15 - 1 ,b.cend());
	c.erase(c.cend() - std::rand() % 15 - 1 ,c.cend());

	for (auto Iter = c.begin(); Iter != c.end(); Iter++ )
		if(count(b.cbegin(), b.cend() ,*Iter) == 0) c.erase(Iter--);
	for (auto Iter = b.begin(); Iter != b.end(); Iter++ )
		if(count(c.cbegin(), c.cend() ,*Iter) == 0) b.erase(Iter--);

	for (auto ex : c )
		std::cout  << ex <<" ";
	std::cout  << "\n\n";
	for (auto ex : b )
		std::cout  << ex <<" ";
	std::cout  << "\n\n";
	return 0;
}