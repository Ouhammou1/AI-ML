#include <iostream>
#include "Contact.h"
#include "PhoneBook.h"

int main()
{
	PhoneBook phone;
	std::string  str ;

	while (true)
	{
		std::cout << "Enter (ADD, SEARCH or  EXIT): " << std::endl;
	    std::getline(std::cin , str);

		if (str == "ADD")
		{
			phone.addContact();
		}
		if(str == "SEARCH")
		{
			phone.addAffiche();
		}
		else if(str == "EXIT")
			exit(0);
	}
	return 0;
}