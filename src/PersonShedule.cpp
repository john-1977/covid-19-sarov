#include "PersonShedule.h"

#include "Location.h"

// добавить локацию в расписание
void PersonShedule::addLocation(Location *location, double timeStartInSeconds, double timeEndInSeconds)
{
    m_sectionList.push_back(PersonSheduleSection(location, timeStartInSeconds, timeEndInSeconds));
}

PersonSheduleSection::PersonSheduleSection(Location *location, double timeStartInSeconds, double timeEndInSeconds)
{
    m_location = location;
    m_timeStartInSeconds = timeStartInSeconds;
    m_timeEndInSeconds = timeEndInSeconds;
}
