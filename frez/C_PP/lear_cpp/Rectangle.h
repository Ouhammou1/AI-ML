#ifndef RECTANGLE_H
#define RECTANGLE_H
// #include "oop.cpp"
#include <iostream>


class Rectangle
{
	private:
		float width;
		float height;
	public:
		float get_width();
		float get_height();
		float get_area();
		void set_width(int x );
		void set_height(int y );
		void set_objet(Rectangle m);

		Rectangle();
		~Rectangle();
		
};


// class Rectangle
// {
// private:
// 	/* data */
// public:
// 	Rectangle(/* args */);	
// 	~Rectangle();
// };

// Rectangle::Rectangle(/* args */)
// {
// }

// Rectangle::~Rectangle()
// {
// }



#endif