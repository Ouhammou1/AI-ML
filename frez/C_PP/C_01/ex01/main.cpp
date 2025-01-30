/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 20:25:53 by bouhammo          #+#    #+#             */
/*   Updated: 2025/01/09 21:34:14 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include  "Zombie.hpp"


// for leaks 
#include <thread>
#include <chrono>


int  main()
{
	int N =5000;
	std::string name = "Foo ";
	
	Zombie *hord = zombieHorde(N, name);

	for (int i = 0; i < N; i++)
	{
		hord[i].announce();
	}

	delete[]  hord;
	// for leaks 	
	// std::this_thread::sleep_for(std::chrono::seconds(100));

	return 0;
}