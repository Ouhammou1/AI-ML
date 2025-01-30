/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:55:06 by bouhammo          #+#    #+#             */
/*   Updated: 2025/01/23 12:30:27 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanB.hpp"

HumanB::HumanB(std::string name): name(name) , weaopn(nullptr)
{
}

HumanB::~HumanB()
{
}

void HumanB::attack()
{
	std::cout << name << " attacks with their ";
	if(weaopn != nullptr)
		std::cout << *weaopn << std::endl;

}

void HumanB::setWeapon(std::string &weaopn)
{
	weaopn = &weaopn;
}



