/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 21:45:37 by bouhammo          #+#    #+#             */
/*   Updated: 2025/01/11 12:11:32 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream> 



int main()
{

	std::string 	str = "HI THIS IS BRAIN";
	std::string 	*stringPTR = &str;
	std::string 	&stringREF = str;

	
	std::cout << "The memory address of the string variable: " << &str << std::endl;
	std::cout << "The memory address held by stringPTR:      " << &stringPTR << std::endl;
	std::cout << "The memory address held by stringREF:      " << &stringREF << std::endl;


	std::cout << "The value of the string variable  :    " << str << std::endl;
	std::cout << "The value pointed to by stringPTR :    " << *stringPTR << std::endl;
	std::cout << "The value pointed to by stringREF :    " << stringREF << std::endl;

	return 0;
}