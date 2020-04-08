#pragma once
#include "Person.h"
#include <list>

// Базовый класс Локаций
class Location
{
public:
    Location() {}
    ~Location() {}

    double m_beta;		// коэффициент перехода от восприимчивого к инкубационному периоду
    double m_alpha;		// коэффициент перехода от инкубационного периода к инфицированию
    double m_gamma;		// коэффициент выздоровления
};

// Локация дом - локация по умолчанию
class Home : public Location
{
public:
    Home() {}
    ~Home() {}

    std::list<Person> m_personList;	// список членов семьи
};

// Класс работа - базовый класс рабочего места
class Work : public Location
{
public:
    Work() {}
    ~Work() {}

    std::list<Employee> m_employeeList;// список работников
};

class VNIIEF : public Location
{
public:
    VNIIEF() {}
    ~VNIIEF() {}

    void addArea() {}

    std::list<Area> m_areaList; // список площадок
};

// Класс площадка
class Area : public Location
{
public:
    Area() {}
    ~Area() {}

    void addFirstDepartment(FirstDepartment *firstDepartment) {}
    void addInputOutput(InputOutput *inputOutput) {}
    void addInputOutput(Canteen *canteen) {}

    FirstDepartment *m_firstDepartment;			// первый отдел
    std::list<InputOutput> m_inputOutputArray;	// список пунктов ввода-вывода
    Canteen *m_canteen;							// столовая
};

// Класс Первый отдел
class FirstDepartment : public Work
{
public:
    FirstDepartment() {}
    ~FirstDepartment() {}

    Area *m_area; // площадка, к которой относится
};

// Класс пункт ввода-вывода
class InputOutput : public Work
{
public:
    InputOutput() {}
    ~InputOutput() {}

    Area *m_area; // площадка, к которой относится
};

// Класс Столовая
class Canteen : public Work
{
public:
    Canteen() {}
    ~Canteen() {}

    Area *m_area; // площадка, к которой относится
};

// Класс отдела
class Department : public Work
{
public:
    Department() {}
    ~Department() {}

    Area *m_area;					    // площадка, к которой относится
    Employee *m_headOfDepartment;	    // начальник отдела
    std::list<Group> m_groupList;       // список групп
};

// Класс группы
class Group : public Work
{
public:
    Group() {}
    ~Group() {}

    // планерка
    void meeting();

    Department *m_department;           // отдел, к которому относится
    Employee *m_headOfGroup;            // начальник
    std::list<Employee> m_employeeList; // список подчиненных
    double m_meetingProbability;        // вероятность планерки
    double m_meetingDuration;           // длительность планерки
};
