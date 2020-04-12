#include "LocationShedule.h"

#include "Person.h"

// добавить агента в расписание
void LocationShedule::addPerson(Person *person, double timeStart, double timeDuration)
{
    // нужно скомпоновать расписание событийно
    // То есть с такого-то по такое-то время были эти агенты, с такого-то по такое-то другие
    // тогда  главном цикле шаг моделирования будет 1 день, цикл будет по локациям
}
