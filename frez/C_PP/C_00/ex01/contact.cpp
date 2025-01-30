/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 10:31:38 by bouhammo          #+#    #+#             */
/*   Updated: 2025/01/03 11:38:57 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Contact.h"


Contact::Contact()
{
}
Contact::~Contact()
{
}
void Contact::set_first_name(std::string first_name)
{
	this->first_name = first_name;
}
void Contact::set_last_name(std::string last_name)
{
	this->last_name = last_name;
}
void Contact::set_nickname(std::string nickname)
{
	this->nickname = nickname;
}
void Contact::set_phone_number(std::string phone_number)
{
	this->phone_number = phone_number;
}
void Contact::set_darkesr_secret(std::string darkesr_secret)
{
	this->darkesr_secret = darkesr_secret;
}


std::string Contact::get_first_name()
{
	return first_name;
}
std::string Contact::get_last_name()
{
	return last_name;
}
std::string Contact::get_nickname()
{
	return nickname;
}
std::string Contact::get_phone_number()
{
	return phone_number;
}
std::string Contact::get_darkesr_secret()
{
	return darkesr_secret;
}