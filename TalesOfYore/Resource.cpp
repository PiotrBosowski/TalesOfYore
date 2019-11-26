#include "Resource.hpp"
using namespace std;

Resource::Resource(std::string resourceName_, double ammount_)
: resourceName{ resourceName_ }, ammount{ ammount_ }
{
}

double Resource::get()
{
	return ammount;
}

void Resource::set(const double newResourceAmmount) //setting ammount to a new flat value, if new value extends max_ammount (or min_ammount), ammount becomes max_ammount (or min_ammount)
{
	if (newResourceAmmount >= min_ammount)
	{
		if (newResourceAmmount <= max_ammount)
			ammount = newResourceAmmount;
		else ammount = max_ammount;
	}
	else ammount = min_ammount;
}

void Resource::gain(const double resourceGain)
{
	ammount += resourceGain;
	if (ammount > max_ammount) ammount = max_ammount;
}

void Resource::lose(const double resourceLoss)
{
	ammount -= resourceLoss;
	if (ammount < min_ammount) ammount = min_ammount;
}

std::string Resource::getName() const
{
	return resourceName;
}

Resource::~Resource()
{

}