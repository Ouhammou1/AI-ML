


#include <iostream>

class Weapon
{
private:
	std::string  type;
public:
	Weapon(std::string type);
	~Weapon();

	const std::string &getType();
	void 		setType(std::string type);

};


Weapon::Weapon(std::string type) : type(type)
{
}

Weapon::~Weapon()
{
}
void	Weapon::setType(std::string type)
{
	this->type = type;
}

const std::string &Weapon::getType() 
{
	return type;
}



class HumanA
{
private:
	Weapon 			&weapon;
	std::string 	name;
public:
	HumanA(Weapon &weapon , std::string name);
	~HumanA();

	
	void attack();
};


HumanA::HumanA(Weapon &weapon , std::string name) : weapon(weapon) , name(name)
{

}

HumanA::~HumanA()
{
	
}
void HumanA::attack()
{
	std::cout << name << " attacks with their " << weapon.getType() << std::endl;
}




int main()
{
	{
		Weapon club = Weapon("crude spiked club");
		HumanA bob(club , "Bob");
		bob.attack();
		club.setType("some other type of club");
		bob.attack();
	}
	// {
	// 	Weapon club = Weapon("crude spiked club");
	// 	HumanB jim("Jim");
	// 	jim.setWeapon(club);
	// 	jim.attack();
	// 	club.setType("some other type of club");
	// 	jim.attack();
	// }
	return 0;
}

