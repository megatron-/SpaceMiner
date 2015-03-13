#ifndef PLANET_H
#define PLANET_H

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <cstdlib>

#include "resource.h"

std::string Spacer(int s)
{
	std::string temp;
	for(int i = 0; i < s; i++) temp += '-';
	return temp;
}

class Planet
{
private:
	std::string p_name;
	std::vector<Resource> p_resources;
	std::vector<Planet> p_moons;
	unsigned int TotalResources()
	{
		unsigned int temp = 0;
		for(auto& i : p_resources) temp += i.Quantity();
		return temp;
	}
	unsigned int TotalValue()
	{
		unsigned int temp = 0;
		for(auto& i : p_resources)
			temp += i.TotalValue();
		return temp;
	}
public:
	Planet(std::string name): p_name(name) {}
	friend std::ostream& operator<<(std::ostream& os, Planet& m)
	{
		os << std::left << "Name: " << m.p_name
		   << "\tResources: " << m.p_resources.size()
		   << "\tMoons: " << m.p_moons.size() << "\n\n"
		   << Spacer(22) << "\n";

		os << std::left << std::setw(12) << "Resource"
		   << std::right << std::setw(4) << "Qty"
		   << std::setw(6) << "Val" << "\n"
		   << Spacer(22) << "\n";

		for(unsigned int i = 0; i < m.p_resources.size(); i++)
			os << m.p_resources[i] << "\n";

		os << Spacer(22) << "\n";

		if(m.p_resources.size() > 1)
		{
			os << std::left << std::setw(12) << "Total:"
			   << std::right << std::setw(4) << m.TotalResources()
			   << std::setw(6) << m.TotalValue() << "\n"
			   << Spacer(22);
		}

		os << "\n\n";

		if(m.Moons() > 0) 
			for(unsigned int i = 0; i < m.Moons(); i++)
				os << "Moon " << i+1 << " " << m.p_moons[i];

		return os;
	}
	bool AddResource(Resource r)
	{
		if(p_resources.size() > 0)
			for(unsigned int i = 0; i < p_resources.size(); i++)
				if(p_resources[i] == r) return 0;

		p_resources.push_back(r);
		return 1;
	}
	bool AddMoon(Planet p) { p_moons.push_back(p); return 1; }
	unsigned int Moons() { return p_moons.size(); }
	unsigned int ResourceTypes() { return p_resources.size(); }
	~Planet() {}
};
// 48-57 = numbers | 65-90 Uppercase
std::string RandomName()
{
	std::string name = "";
	for(unsigned int i = 0; i < 3; i++)
	{
		char temp = rand() % 26 + 65;
		name += temp;
	}
	name += '-';
	for(unsigned int i = 0; i < 4; i++)
	{
		char temp = rand() % 10 + 48;
		name += temp;
	}
	return name;
}

Planet RandomPlanet(unsigned int resourceamount = 1, int maxresource = 100, unsigned int maxmoons = 0)
{
	if(resourceamount > ResourceList.size())
		resourceamount = ResourceList.size();
	Planet m(RandomName());
	unsigned int amount = rand() % resourceamount + 1;
	while(m.ResourceTypes() < amount)
	{
		int res = rand() % ResourceList.size();
		int qty = rand() % maxresource + 1;
		Resource r = ResourceList[res];
		r.SetQuantity(qty);
		m.AddResource(r);
	}
	if(maxmoons == 0) return m;
	unsigned int moons = rand() % maxmoons + 1;
	while(m.Moons() < moons)
	{
		Planet moon = RandomPlanet(resourceamount/2, maxresource/2);
		m.AddMoon(moon);
	}
	return m;
}

#endif
