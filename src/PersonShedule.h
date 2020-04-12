#pragma once
#include <map>

class Location;

// Класс расписание агента
// Содержит список локаций, которые посетит сегодня и время их посещения
class PersonShedule
{
public:
	PersonShedule() {}
	~PersonShedule() {}

	void addLocation(Location *location, double timeStart, double timeDuration);

	//std::map<double, Location *> m_shedule;
};
