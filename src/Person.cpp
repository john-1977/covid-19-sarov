#include "Person.h"

#include "Location.h"

Person::Person()
{
}

void Person::generateDayOffShedule()
{
	m_shedule.addLocation(m_home, 0, 24 * 60 * 60);
}

// Сообщить локации о своем присутствии сегодня
void Person::notifyLocations()
{
    for (size_t i = 0; i < m_shedule.m_sectionList.size(); ++i)
    {
        PersonSheduleSection currentSection = m_shedule.m_sectionList.at(i);
        currentSection.m_location->m_locationShedule.addPerson(this, currentSection.m_timeStartInSeconds, currentSection.m_timeEndInSeconds);
    }
}

void StayAtHome::generateShedule()
{
	m_shedule.addLocation(m_home, 0, 24 * 60 * 60);
}

void OrganizationEmployee::generateShedule()
{
	m_shedule.addLocation(m_home, 0, 24 * 60 * 60);
	m_shedule.addLocation(m_group, timeStartWorkingInSeconds, timeEndWorkingInSeconds); // работа
	// поход к начальнику отдела
	// поход в архив
	// поход в библиотеку
	// поход в столовую
}

void ArchiveEmployee::generateShedule()
{
	m_shedule.addLocation(m_home, 0, 24 * 60 * 60);
	m_shedule.addLocation(m_archive, timeStartWorkingInSeconds, timeEndWorkingInSeconds); // работа в архиве
}

void LibraryEmployee::generateShedule()
{
	m_shedule.addLocation(m_home, 0, 24 * 60 * 60);
	m_shedule.addLocation(m_library, timeStartWorkingInSeconds, timeEndWorkingInSeconds); // работа в библиотеке
}

void CanteenEmployee::generateShedule()
{
    m_shedule.addLocation(m_home, 0, 24 * 60 * 60);
	m_shedule.addLocation(m_canteen, timeStartWorkingInSeconds, timeEndWorkingInSeconds); // работа в столовой
}
