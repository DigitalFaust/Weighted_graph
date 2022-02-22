#include<iostream>
#include<limits>

int main()
{
	int max = std::numeric_limits<int>::max();

	std::cout << "max = " << max << std::endl;
	std::cout << "max + max = " << max + max << std::endl;
	std::cout << max + 1 << std::endl;

	return 0;
}
