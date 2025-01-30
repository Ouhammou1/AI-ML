#include "student.hpp"



student::student(int g)
{
	(void)g;
	// std::cout <<  "g = " << g <<std::endl;

}

student::student(int g , std::string name ):person(name)
{
	std::cout << " number is |" << g << "|" << std::cin;
}
student::student()
{
	std::cout << " STUDENT  \n" << std::endl;
}

student::~student()
{
}

int student::getCounter()
{
	return counter;
}
void student::setCounter(int counter)
{
	this->counter = counter;
}

float student::getGrade()
{
	return grade;
}
void 	student::setGrade(int grade)
{
	this->grade = grade;
}