#pragma once

#include <vector>

class Person;
class Location;

// Класс модель
// Содержит список всех агентов, список всех локаций
// Управляет моделированием
class Model
{
public:
    Model() {}
    ~Model() {}

    std::vector<Person *> allPersons;
    std::vector<Location *> allLocations;
};
