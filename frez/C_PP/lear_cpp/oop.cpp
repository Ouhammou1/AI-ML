
// CLASS : A user-defined data type that can be used to store together elements of 
// Object  it is an instance of a class
// different  data types &  functions and it works as a blueprint for creation objects.

// CLASS ---> Because it's the blueprint that we use to make  objects  

// #include "Rectangle.h"

// #include <iostream> 
 





// #include <iostream>

// class oop
// {
// private:
// 	int y;
// public:
// 	oop();
// 	~oop();
// 	int   get_y();
// };

// oop::oop()
// {
// 	y = 46468;

// }

// oop::~oop()
// {
// }
// int   oop::get_y()
// {
// 	return y;
// }


// int main()
// {
// 	oop r;

// 	std::cout << "y = " << r.get_y() << std::endl;
	
// 	return 0;
// }



// class Rectangle
// {
// 	private:
// 		float width;
// 		float height;
// 	public:
// 		float get_width();
// 		float get_height();
// 		float get_area();
// 		void set_width(float x );
// 		void set_height(float y );
// 		void set_objet(Rectangle m);
// 		Rectangle operator ++();
// 		Rectangle operator ++(int);
// 		Rectangle operator +(Rectangle r , Rectangle rr);
// 		Rectangle();
// 		Rectangle(float x , float y );
// 		~Rectangle();
		
// };

// Rectangle Rectangle::operator +(Rectangle r )
// {
// 	Rectangle newR;
// 	newR.set_width(width + r.get_width() ) ;
// 	newR.set_height(height + r.get_height());
// 	return newR;
// }
// float Rectangle::get_width()
// {
// 	return width;
// }

// float  Rectangle::get_height(){
// 	return height;
// }
// void Rectangle::set_width(float x) 
// {
// 	this->width = x;
// }

// void  Rectangle::set_height( float y ){
// 	this->height = y;
// }

// Rectangle::Rectangle(float x , float y)
// {
// 	width = x;
// 	height = y;

// }


// Rectangle Rectangle::operator++()
// {
// 	for (int i = 0; i < 100; i++)
// 	{
//     	++width;
//     	++height;
// 	}
	
//     return Rectangle(width, height);
// }

// Rectangle Rectangle::operator++(int)
// {
// 	for (int i = 0; i < 100; i++)
// 	{
//     	width++;
//     	height++;
// 	}
	
//     return Rectangle(width, height);
// }

// Rectangle::Rectangle()
// {
// }
// Rectangle::~Rectangle()
// {	
// }

// int main()
// {
//     Rectangle r1;
// 	r1.set_width(3);
// 	r1.set_height(5);


//     Rectangle r4 = r1++;
//  	std::cout << "Width of r4: " << r4.get_width() << std::endl;
//     std::cout << "Height of r4: " << r4.get_height() << std::endl;

// 	std::cout << "Width of r1: " << r1.get_width() << std::endl;
//     std::cout << "Height of r1: " << r1.get_height() << std::endl;
// 	Rectangle r5 = r4 + r1;

//     std::cout << "Width of r4: " << r5.get_width() << std::endl;
//     std::cout << "Height of r4: " << r5.get_height() << std::endl;

//     return 0;
// }




// class student
// {
// private:
// 	std::string firstname;
// 	std::string lastname;
// 	float grade;
// 	static int counter ;
// public:
// 	void setFirstName(std::string str);
// 	std::string  getFirstName();
// 	int getcouter();
// 	// void setcouter();



// 	student();
// 	~student();
// };

// int student::counter = 0;

// student::student(/* args */)
// {
// 	counter++;
// }

// student::~student()
// {
// }

// void student::setFirstName(std::string str)
// {
// 	this->firstname = str;
// }
// std::string student::getFirstName()
// {
// 	return firstname;
// }
// int student::getcouter()
// {
// 	return counter;
// }




// int main()
// {
// 	student s1, s2,s3, s4;
// 	s1.setFirstName("BRAHIM ");

// 	std::cout  << s1.getcouter()  <<  std::endl;
// 	std::cout  << s2.getcouter()  <<  std::endl;
// 	std::cout  << s3.getcouter()  <<  std::endl;
// 	std::cout  << s4.getcouter()  <<  std::endl;

// }





// class calculater
// {
// private:
// public:
// 	static  int add( int x , int y );
// 	static  int add( int x , int y , int z  );
// 	calculater(/* args */);
// 	~calculater();
// };

// calculater::calculater(/* args */)
// {
// }

// calculater::~calculater()
// {
// }
 
// int calculater::add(int x , int y )
// {
// 	int sum = 0;
// 	sum  = x + y ;
// 	return sum;
// }
// int calculater::add(int x , int y  , int z )
// {
// 	int sum = 0;
// 	sum  = x + y + z;
// 	return sum;
// }


// int main()
// {
	
// 	calculater j;
// 	calculater k;
// 	std::cout  << "Add is " << calculater::add(45,56) << std::endl;
// 	std::cout  << "Add is " << calculater::add(4,5,6) << std::endl;
// 	std::cout  << "Add is " << j + k << std::endl;
	
// 	return 0;
// }




















// // #include <iostream>
// // #include <list>

// // class youtube
// // {
// // public:
// // 	std::string name;
// // 	std::string owner_name;
// // 	int nbr_sub;
// // 	std::list<std::string> publishedvid;

// // 	//constructor
// // 	youtube(std::string name_ , std::string owner_name_ )
// // 	{
// // 		name = name_;
// // 		owner_name = owner_name_;
// // 		nbr_sub = 0;
// // 	}
// // 	void GetInfo()
// // 	{
// // 		std::cout << "Name : " << name << std::endl;
// // 		std::cout << "owner_name : " << owner_name << std::endl;
// // 		std::cout << "nbr_sub : " << nbr_sub << std::endl;
// // 		std::cout << "Videos : " << std::endl;

// // 	for (std::list<std::string>::iterator it = publishedvid.begin(); it != publishedvid.end(); ++it)
// //     {
// //         std::cout << "				" << *it << std::endl;
// //     }
		

// // 	}

// // };

// // int main()
// // {
// //     // Use the constructor to initialize the object
// //     youtube ok("brahim ouhammou", "Coding school");
// // 	ok.publishedvid.push_back("C++ & C");
// // 	ok.publishedvid.push_back("PYTHON ");
// // 	ok.publishedvid.push_back("PHP");
// // 	ok.publishedvid.push_back("JAVA");


// //     ok.GetInfo();

// //     return 0;
// // }






// // Create youtube channel 



// #include <iostream>

// class y_channel
// {
// private:
// 	std::string name;
// 	std::string owner_name;
// 	int num_sub;
// public:

// 	void get_info();
// 	void subdcribe();

// 	void set_name(std::string name);
// 	void set_owner_name(std::string owner_name);
// 	void set_num_sub(int n);

// 	// std::string get_name();
// 	// std::string get_owner_name();


// 	y_channel();
// 	~y_channel();
// };


// void y_channel::set_num_sub(int n)
// {
// 	this->num_sub = n;
// }

// void y_channel::set_name( std::string name)
// {
// 	this->name = name;
// }
// void y_channel::set_owner_name( std::string owner_name)
// {
// 	this->owner_name = owner_name;
// }


// void y_channel::subdcribe()
// {
// 	num_sub+=450;
// }

// void  y_channel::get_info()
// {
// 	std::cout <<  "Name " << name << std::endl;
// 	std::cout <<  "Owner_name " << owner_name << std::endl;
// 	std::cout <<  "num_sub  " << num_sub << std::endl;

// }

// y_channel::y_channel(/* args */)
// {
// 	std::cout  << "The first  function execute  i class " << std::endl;
// }

// y_channel::~y_channel()
// {
// 	std::cout  << "The last  function execute  i class " << std::endl;
// }


// int main()
// {
// 	y_channel youtub;  

// 	youtub.set_name("brahim ");
// 	youtub.set_owner_name("OUHABEST");
// 	youtub.set_num_sub(100);

// 	// youtub.set_num_sub();
// 	for (size_t i = 0; i < 410; i++)
// 	{
// 		youtub.subdcribe();
// 	}
	
// 	youtub.get_info();
// 	std::cout <<  " ----------------------------------------------------- " << std::endl;

// 	return 0;
// }