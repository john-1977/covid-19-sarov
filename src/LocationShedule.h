#pragma once

#include <list>
#include "Location.h"

// Класс расписание в локации
// содержит список отрезков времени, внутри которых состав агентов в локации не менялся
// внутри каждого такого отрезка происходит моделирование
class LocationShedule
{
public:
    LocationShedule() {}
    ~LocationShedule() {}

    void addPerson(Person *person, double timeStart, double timeDuration);

    std::list<LocationSheduleSection> m_shedule; // <время начала отрезка, время конца отрезка, агенты>
};

class LocationSheduleSection
{
public:
    LocationSheduleSection() {}
    ~LocationSheduleSection() {}
    double m_timeStart;
    double m_timeEnd;
    std::list<Person *> m_personList;
};
