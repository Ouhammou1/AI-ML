/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 20:08:56 by bouhammo          #+#    #+#             */
/*   Updated: 2025/01/09 21:20:21 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMNIE_H
#define ZOMNIE_H

#include <iostream>


class Zombie
{
private:
	std::string name;

public:
	Zombie();
	~Zombie();

	void announce();
	void SetName(std::string  name);
};

Zombie* zombieHorde( int N, std::string name);

#endif 
