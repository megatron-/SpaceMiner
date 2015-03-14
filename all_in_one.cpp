
///resource.h ///////////////////////////////////////////////////////////////////////////
#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime> ////
class Resource
{
private:
	std::string p_name;
	int p_basevalue;
	int p_quantity;
public:	
	Resource(std::string name, int basevalue, int quantity=0) //
	: p_name(name), p_basevalue(basevalue), p_quantity(quantity) {}
	void SetQuantity(int qty) { p_quantity = qty; }
	int Quantity() const { return p_quantity; }
	int Value() const { return p_basevalue; }
	int TotalValue() const { return p_basevalue * p_quantity; }
	std::string Name() const { return p_name; }
	friend std::ostream& operator<<(std::ostream& os, Resource& r)
	{
		os << std::left << std::setw(12) << r.p_name;
		os << std::right << std::setw(4) << r.p_quantity;
		os << std::right << std::setw(6) << r.TotalValue();
		return os;
	}
	bool operator==(Resource r)
	{
		if(p_name == r.p_name) return true;
		return false;
	}
	~Resource() {}
};


std::vector<Resource> ResourceList;
		
void Init()
{
	static bool done = 0;
	if(done) return;

	srand(time(0));
	ResourceList.push_back(Resource("Hydrogen",15,0));
	ResourceList.push_back(Resource("Helium",10,0));
	ResourceList.push_back(Resource("Lithium",8,0));
	ResourceList.push_back(Resource("Beryllium",7,0));
	ResourceList.push_back(Resource("Boron",6,0));
}

Resource RandomResource(int quantity = 1)
{
	Resource r = ResourceList[rand() % ResourceList.size()];
	r.SetQuantity(quantity<1 ? 1 : rand() % quantity + 1 );
	return r;
}

#endif 
///end of resource.h ////////////////////////////////////////////////////////////////////


///planet.h /////////////////////////////////////////////////////////////////////////
#ifndef PLANET_H
#define PLANET_H

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <cstdlib>
//#include "resource.h"

std::string Spacer(int s)
{ 
	return std::string(s,'-');  
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
		for(unsigned int i = 0; i < p_resources.size(); i++)
			temp += p_resources[i].Quantity();
		return temp;
	}
	unsigned int TotalValue()
	{
		unsigned int temp = 0;
		for(unsigned int i = 0; i < p_resources.size(); i++)
			temp += p_resources[i].Quantity();
		return temp;
	}
public:
	Planet(std::string name): p_name(name) {}
	friend std::ostream& operator<<(std::ostream& os, Planet& m)
	{
		os << std::left << "Name: " << m.p_name << "\tResources: " << m.p_resources.size() 
			<< "\tMoons: " << m.p_moons.size() << "\n\n" << Spacer(22) << "\n" << std::left 
			<< std::setw(12) << "Name" << std::right << std::setw(4) << "Qty" << std::setw(6) 
			<< "Val" << "\n" << Spacer(22) << "\n";
		
		for(unsigned int i = 0; i < m.p_resources.size(); i++) os << m.p_resources[i] << "\n";
		os << Spacer(22) << "\n";
		if(m.p_resources.size() > 1)
		{
			os << std::left << std::setw(12) << "Total:" << std::right << std::setw(4) << m.TotalResources() << std::setw(6) << m.TotalValue() << "\n";
			os << Spacer(22);
		}
		os << "\n\n";
		if(m.Moons() > 0) 
		{
			for(unsigned int i = 0; i < m.Moons(); i++) os << "Moon " << i+1 << " " << m.p_moons[i];
		}
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


std::string RandomName()
{
	std::string name = "AAA-0000";
	for(int i = 0; i < 3; i++)			 
		name[i] += rand() % 26;	
	
	for(int i = 4; i < 8; i++)			
		name[i] += rand() % 10;
	
	return name;
}

Planet RandomPlanet(unsigned int resourceamount = 1, int maxresource = 100, unsigned int maxmoons = 0)
{
	if(resourceamount > ResourceList.size()) resourceamount = ResourceList.size();
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
///end of planet.h /////////////////////////////////////////////////////////////////////



///main.cpp/////////////////////////////////////////////////////////////////////////////
#include <iostream>
//#include "resource.h"
//#include "planet.h"

int main()
{
	std::cout << "wellcome!\n\n";	
	Init();	
	Planet m = RandomPlanet(5, 100, 6);
	std::cout << m << "\n";
	
	return 0;
}
///end of main.cpp //////////////////////////////////////////////////////////////////////
