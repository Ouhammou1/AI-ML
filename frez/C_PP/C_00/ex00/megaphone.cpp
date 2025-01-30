#include <iostream>

void 	convert_to_upper(std::string str)
{
	int i ;

	i = 0;
	while (str[i] !='\0')
	{
		if (str[i] >= 'a' && str[i] <= 'z') { 
            str[i] -= 32;
			std::cout << str[i];
        }
		else
			std::cout << str[i];
		i++;
	}
	return ;
}
int main(int ac  , char *av[])
{

	int i;

	if(ac == 1)
	{
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
		return 0;
	}
	i = 1;
	while (i < ac)
	{
		convert_to_upper(av[i]);
		i++;
	}
	std::cout << std::endl;
	return 0;
}