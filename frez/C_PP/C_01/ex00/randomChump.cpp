/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randomChump.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 21:14:47 by bouhammo          #+#    #+#             */
/*   Updated: 2025/01/08 21:47:42 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include <iostream>
#include "Zombie.hpp"

void randomChump( std::string name)
{
	Zombie Zombie(name);
	
	Zombie.announce();
}