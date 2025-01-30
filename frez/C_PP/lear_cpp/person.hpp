


#ifndef PERSON_H
#define PERSON_H


#include <iostream>


class person
{
private:
	std::string name;
	int age;
	std::string address;

public:
	person();
	person(std::string nn);
	~person();

	std::string get_name();
	void set_name(std::string name);

	int 	get_age();
	void 	set_age(int age);
};


#endif