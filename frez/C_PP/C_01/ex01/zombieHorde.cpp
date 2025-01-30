/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 20:36:21 by bouhammo          #+#    #+#             */
/*   Updated: 2025/01/09 21:24:35 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie	*zombieHorde(int N, std::string name)
{
	Zombie *hord = new Zombie[N];
	if (hord == nullptr)
	{
		return NULL;
	}
	for (int i = 0; i < N; i++)
	{
		hord[i].SetName(name);
	}
	return hord;
}