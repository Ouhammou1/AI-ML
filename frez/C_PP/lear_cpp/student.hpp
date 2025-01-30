
#ifndef STUDENT_H
#define STUDENT_H


#include <iostream>
#include "person.hpp"


class student:public  person
{
private:
	float grade;
	int counter;
public:

	int 	getCounter();
	void 	setCounter(int counter);
	float 	getGrade();
	void 	setGrade(int grade);

	student();
	student(int g , std::string name);
	student(int g);
	~student();
};

#endif