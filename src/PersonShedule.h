#pragma once
#include <map>
#include "Location.h"

class PersonShedule
{
public:
	PersonShedule() {}
	~PersonShedule() {}

	void addLocation(Location *location, double timeStart, double timeDuration);

	std::map<double, Location *> m_shedule;
};