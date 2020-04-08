#include "Person.h"

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

void VNIIEFEmployee::generateShedule()
{
	m_shedule.addLocation(m_home, 0, 24 * 60);
	m_shedule.addLocation(m_group, timeStartWorking, timeEndWorking - timeStartWorking); // работа
	// поход к начальнику отдела
	// поход в первый отдел
	// поход в пункт ввода-вывода
	// поход в столовую
}

void FirstDepartmentEmployee::generateShedule()
{
	m_shedule.addLocation(m_home, 0, 24 * 60);
	m_shedule.addLocation(m_firstDepartment, timeStartWorking, timeEndWorking - timeStartWorking); // работа в первом отделе
}

void InputOutputEmployee::generateShedule()
{
	m_shedule.addLocation(m_home, 0, 24 * 60);
	m_shedule.addLocation(m_inputOutput, timeStartWorking, timeEndWorking - timeStartWorking); // работа в пункте ввода-вывода
}

void CanteenEmployee::generateShedule()
{
	m_shedule.addLocation(m_home, 0, 24 * 60);
	m_shedule.addLocation(m_canteen, timeStartWorking, timeEndWorking - timeStartWorking); // работа в столовой
}
