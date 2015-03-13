#include <iostream>

#include "resource.h"
#include "planet.h"

int main()
{
	Init();
	std::vector<Planet> temp;
	for(unsigned int j = 0; j < 50; j++)
	{
		temp.push_back(RandomPlanet(5, 1000, 2));
	}
	std::cout << "50 Random planets created!";
	return 0;
}
