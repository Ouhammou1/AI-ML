/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 14:03:13 by bouhammo          #+#    #+#             */
/*   Updated: 2025/01/03 11:30:03 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONE_BOOK_H
#define PHONE_BOOK_H
#include <iostream>
#include "Contact.h"




class PhoneBook
{
private:
	Contact ary_contact[8];
	int index;
	int Max_Contacts;
public:
	// void set_ary_contact();
	int get_index();
	void addContact();
	void addAffiche();


	PhoneBook();
	~PhoneBook();
};



#endif
