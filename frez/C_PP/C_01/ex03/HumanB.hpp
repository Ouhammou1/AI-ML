/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 10:25:11 by bouhammo          #+#    #+#             */
/*   Updated: 2025/01/23 12:30:35 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef HUMANB_HPP
#define HUMANB_HPP

#include  "Weapon.hpp"

	class HumanB
	{
	private:
		std::string name;
		std::string *weaopn;
	public:
		HumanB(std::string name);
		~HumanB();

		void setWeapon(std::string &weaopn);
		void 	attack();
	};





#endif