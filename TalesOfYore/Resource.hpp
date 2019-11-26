#pragma once
#include <string>

class Resource
{
public:
	Resource(std::string resourceName_, double ammount_);
	double get();
	void set(double newResourceAmmount);
	void gain(double resourceGain);
	void lose(double resourceLoss);
	std::string getName() const;
	~Resource();

private:
	const std::string resourceName;
	double ammount;
	const double min_ammount = 0, max_ammount = 100;
};