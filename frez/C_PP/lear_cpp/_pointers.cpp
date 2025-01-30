#include <iostream> 


class Box
{
private:
	float volume;
public:
	int  getVolume();
	void SetVolume(float volume);

	Box(float val);
	~Box();
};

void Box::SetVolume(float volume)
{
	this->volume = volume;
}

int  Box::getVolume()
{
	return volume;
}

Box::Box( float val)
{
	volume = val;
}

Box::~Box()
{
}

class BoxManger
{
private:
	Box &box;
public:
	BoxManger(Box &boxref);
	~BoxManger();
	void updateVolume(float newVolume);
	void displayVolume();
};

void BoxManger::displayVolume()
{
	std::cout << "Current Box Volume: " << box.getVolume() << std::endl;
}

void BoxManger::updateVolume(float newVolume)
{
	box.SetVolume(newVolume);
}
BoxManger::BoxManger(Box &box) : box(box)
{
}

BoxManger::~BoxManger()
{
}


int main()
{
	Box myBpx(50.01);
	
	std::cout << "Initial Box Volume: " << myBpx.getVolume() << std::endl;

	BoxManger manager(myBpx);

	manager.updateVolume(1337.42);
	manager.displayVolume();

}








