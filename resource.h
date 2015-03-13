#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <cstdlib>

class Resource
{
private:
	std::string p_name;
	int p_basevalue;
	int p_quantity;
public:	
	Resource(std::string name, int basevalue): p_name(name), p_basevalue(basevalue), p_quantity(0) {}
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

Resource hydrogen("Hydrogen", 15);
Resource helium("Helium", 10);
Resource lithium("Lithium", 8);
Resource beryllium("Beryllium", 7);
Resource boron("Boron", 6);

std::vector<Resource> ResourceList;

void Init()
{
	static bool done = 0;
	if(done) return;

	srand(time(0));
	ResourceList.push_back(hydrogen);
	ResourceList.push_back(helium);
	ResourceList.push_back(lithium);
	ResourceList.push_back(beryllium);
	ResourceList.push_back(boron);
}

Resource RandomResource(int quantity = 1)
{
	int temp;
	if(quantity <= 0) temp = 1;
	else temp = rand() % quantity + 1;
	int res = rand() % ResourceList.size();
	Resource r = ResourceList[res];
	r.SetQuantity(temp);
	return r;
}

#endif
