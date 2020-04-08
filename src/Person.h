#pragma once
#include "Location.h"
#include "PersonShedule.h"
#include "SEIR_model.h"

// Базовый класс агента, имеет расписание на день, текущее состояние
class Person
{
public:
	Person();
	~Person() {}

	virtual void generateShedule() {}	// генерация расписания рабочего дня
	void generateDayOffShedule();		// генерация расписания выходного дня

	SEIR_State m_state;			// состояние по SEIR-модели
	Location *m_home;			// локация по-умолчанию
	PersonShedule m_shedule;	// расписание на день
};

// Класс домосед - сидит дома 24/7
class StayAtHome : public Person
{
public:
	StayAtHome() {}
	~StayAtHome() {}

	void generateShedule();
};

// Класс работник, имеет время прихода на работу и ухода с работы
class Employee : public Person
{
public:
	Employee() {}
	~Employee() {}

	virtual void generateShedule() {}

	double timeStartWorking;	// время прихода на работу
	double timeEndWorking;		// время ухода с работы
};

// Класс работник ВНИИЭФ
// относится к своей группе (она относится к отделу и т.д.)
// может ходить к начальнику отдела, в первый отдел, в пункт ввода-вывода, в столовую
class VNIIEFEmployee : public Employee
{
public:
	VNIIEFEmployee() {}
	~VNIIEFEmployee() {}

	virtual void generateShedule();

	Group *m_group;							// группа, к которой относится
	double m_headOfDepartmentProbability;	// вероятность пойти к начальнику отдела
	double m_headOfDepartmentTime;			// время посещения начальника отдела
	double m_FirstDepartmentProbability;	// вероятность пойти в первый отдел
	double m_FirstDepartmentTime;			// время посещения первого отдела
	double m_inputOutputProbability;		// вероятность пойти в пункт ввода-вывода
	double m_inputOutputTime;				// время посещения пункта ввода-вывода
	double m_canteenProbability;			// вероятность пойти в столовую
	double m_canteenTime;					// время посещения столовой
};

// Класс работник первого отдела
// относится к своему первому отделу
// может ходить в столовую
// ходит в пункт ввода-вывода?
class FirstDepartmentEmployee : public VNIIEFEmployee
{
public:
	FirstDepartmentEmployee() {}
	~FirstDepartmentEmployee() {}

	virtual void generateShedule();

	FirstDepartment *m_firstDepartment;	// первый отдел, к которому относится
};

// Класс работник пункта ввода-вывода
// относится к своему пункту ввода-вывода
// может ходить в столовую
// ходит в первый отдел?
class InputOutputEmployee : public VNIIEFEmployee
{
public:
	InputOutputEmployee() {}
	~InputOutputEmployee() {}

	virtual void generateShedule();

	InputOutput *m_inputOutput;	// пункт ввода-вывода, к которому относится
};

// Класс работник столовой
// относится к своей столовой
class CanteenEmployee : public Employee
{
public:
	CanteenEmployee() {}
	~CanteenEmployee() {}

	virtual void generateShedule();

	Canteen *m_canteen;	// столовая, к которой относится
};
