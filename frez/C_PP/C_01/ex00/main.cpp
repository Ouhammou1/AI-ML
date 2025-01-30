
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:17:02 by bouhammo          #+#    #+#             */
/*   Updated: 2025/01/07 13:18:53 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"


#include <thread>
#include <chrono>


int main()
{
	Zombie *newZom = newZombie("Foo");
	randomChump("zombbbb");
	delete newZom;

	std::this_thread::sleep_for(std::chrono::seconds(100));
	return 0;
}