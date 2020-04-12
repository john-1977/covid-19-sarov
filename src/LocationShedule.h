#pragma once

#include <list>

class Person;

// Класс отрезок времени, внутри которых состав агентов в локации не менялся
class LocationSheduleSection
{
public:
    LocationSheduleSection() {}
    ~LocationSheduleSection() {}
    double m_timeStart;
    double m_timeEnd;
    std::list<Person *> m_personList;
};

// Класс расписание в локации на текущий день моделирования
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
