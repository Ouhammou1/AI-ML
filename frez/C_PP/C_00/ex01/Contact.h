/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contact.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 14:05:35 by bouhammo          #+#    #+#             */
/*   Updated: 2025/01/03 10:52:53 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CONTACT_H
#define CONTACT_H
#include <iostream>




class Contact
{
private:
	std::string first_name;
	std::string last_name;
	std::string nickname;
	std::string  phone_number;
	std::string  darkesr_secret;

public:
	void set_first_name(std::string first_name);
	void set_last_name(std::string last_name);
	void set_nickname(std::string nickname);
	void set_phone_number(std::string phone_number);
	void set_darkesr_secret(std::string darkesr_secret);

	std::string get_first_name();
	std::string get_last_name();
	std::string get_nickname();
	std::string get_phone_number();
	std::string get_darkesr_secret();

	Contact();
	~Contact();

};


#endif