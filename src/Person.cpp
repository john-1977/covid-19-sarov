#include "Person.h"

#include "Location.h"

Person::Person()
{
}

void Person::generateDayOffShedule()
{
	m_shedule.addLocation(m_home, 0, 24 * 60);
}

void StayAtHome::generateShedule()
{
	m_shedule.addLocation(m_home, 0, 24 * 60);
}

void OrganizationEmployee::generateShedule()
{
	m_shedule.addLocation(m_home, 0, 24 * 60);
	m_shedule.addLocation(m_group, timeStartWorking, timeEndWorking - timeStartWorking); // работа
	// поход к начальнику отдела
	// поход в архив
	// поход в библиотеку
	// поход в столовую
}

void ArchiveEmployee::generateShedule()
{
	m_shedule.addLocation(m_home, 0, 24 * 60);
	m_shedule.addLocation(m_archive, timeStartWorking, timeEndWorking - timeStartWorking); // работа в архиве
}

void LibraryEmployee::generateShedule()
{
	m_shedule.addLocation(m_home, 0, 24 * 60);
	m_shedule.addLocation(m_library, timeStartWorking, timeEndWorking - timeStartWorking); // работа в библиотеке
}

void CanteenEmployee::generateShedule()
{
	m_shedule.addLocation(m_home, 0, 24 * 60);
	m_shedule.addLocation(m_canteen, timeStartWorking, timeEndWorking - timeStartWorking); // работа в столовой
}
