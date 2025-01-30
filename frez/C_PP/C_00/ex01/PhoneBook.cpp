/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 11:16:15 by bouhammo          #+#    #+#             */
/*   Updated: 2025/01/03 11:29:12 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "PhoneBook.h"
#include <iomanip>

PhoneBook::PhoneBook()
{
	this->index = 0;
	this->Max_Contacts = 0;
}

PhoneBook::~PhoneBook()
{

}
int 	PhoneBook::get_index()
{
	return index;
}


int	checkValid(std::string str)
{
	if(str.empty())
		return 1;
	int i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return 0;
		i++;
	}
	if (i == str.length())
		return 1;
	
	return 0;
}

void PhoneBook::addContact()
{

	std::string first_name;
	std::string last_name;
	std::string nickname;
	std::string  phone_number;
	std::string  darkesr_secret;

	std::cout << "Enter First Name        :";
    std::getline(std::cin , first_name);
    if (checkValid(first_name) == 1) {
        std::cout << "Invalid first name!" << std::endl;
        return;
    }
	std::cout << "Enter last_name         :";
	std::getline(std::cin , last_name );
	if (checkValid(last_name) == 1)
	{
        std::cout << "Invalid first name!" << std::endl;
		return;
	}
	std::cout << "Enter nickname          :";
	std::getline(std::cin , nickname );
	if (checkValid(nickname) == 1)
	{
        std::cout << "Invalid first name!" << std::endl;
		return;
	}
	std::cout << "Enter phone_number      :";
	std::getline(std::cin , phone_number );
	if (checkValid(phone_number) == 1)
	{
        std::cout << "Invalid first name!" << std::endl;
		return;
	}
	std::cout << "Enter darkesr_secret    :";
	std::getline(std::cin , darkesr_secret) ;
	if (checkValid(darkesr_secret) == 1)
	{
        std::cout << "Invalid first name!" << std::endl;
		return;
	}
	this->ary_contact[index].set_first_name(first_name);
	this->ary_contact[index].set_last_name(last_name);
	this->ary_contact[index].set_nickname(nickname);
	this->ary_contact[index].set_phone_number(phone_number);
	this->ary_contact[index].set_darkesr_secret(darkesr_secret);
	index++;
	if(Max_Contacts < 9 )
		Max_Contacts++;
}

void		PrintFerstLine()
{

	std::cout <<  "Index  " << " | ";
	std::cout <<  "First name" << " | ";
	std::cout <<  "Last  name" << " | ";
	std::cout <<  "Nick  name" << std::endl;
	return;

}

void 		PhoneBook::addAffiche()
{
	PrintFerstLine();
	for (int i = 0; i < Max_Contacts; i++)
	{
		std::cout <<  "      " << i << " | ";
		std::cout  << std::setw(10) << this->ary_contact[i].get_first_name();
		std::cout   << " | ";

		std::cout  << std::setw(10) << this->ary_contact[i].get_last_name();
		std::cout   << " | ";

		std::cout  << std::setw(10) << this->ary_contact[i].get_nickname() << std::endl;
	}

	int nbr;
	std::cout << "Enter Index : ";
	std::cin >> nbr;
	if ( nbr < 0 || nbr >= Max_Contacts)
	{
		std::cout << "Error: Index out of range!" << std::endl;
		return ;
	}
	for (int j = 0; j < Max_Contacts; j++)
	{
		if ( j == nbr)
		{
			std::cout << "First name      :"<< this->ary_contact[j].get_first_name() << std::endl;
			std::cout << "Last  name      :"<< this->ary_contact[j].get_last_name() << std::endl;
			std::cout << "Nick  name      :"<< this->ary_contact[j].get_nickname() << std::endl;
			std::cout << "Phone number    :"<< this->ary_contact[j].get_phone_number() << std::endl;
			std::cout << "Darkesr secret  :"<< this->ary_contact[j].get_darkesr_secret() << std::endl;
			return;
		}
	}
}


