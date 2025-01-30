
#include "person.hpp"

person::person(std::string nn)
{

	std::cout << " Name  is == " << nn << std::endl;
}

person::~person()
{
}
person::person()
{
	std::cout << " PERSON \n" << std::endl;
}

void person::set_name(std::string name)
{
	this->name = name;
}
std::string person::get_name()
{
	return name;
}

int 	person::get_age()
{
	return age;	
}

void 	person::set_age(int age)
{
	this->age = age;
}