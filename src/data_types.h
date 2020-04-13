#ifndef _DATA_TYPES_MIGRATION_
#define _DATA_TYPES_MIGRATION_

#include <iostream>
#include <time.h>
#include <list>
/*
	������������ ����� ������� (����� ������ �� ����������������� �����).
*/

struct LocationConfig
{
	int location_id;	// ���������� ������������� �������, ���������� ���������� �������, ���������� �������, �������� � �.�. ������������� �������������.
	time_t start_time;	// �����, ������� � �������� ����� ������������ ����� ���������� � ������ �������. 
	time_t end_time;	// �����, ������� � �������� ���������� � ������ ������� ����� ����������.
	int min_time;		// ����������� �����, � ������� �������� ����� ���������� � ������ �������. �������� � ��������.
	int max_time;		// ������������ �����, � ������� �������� ����� ���������� � ������ �������. �������� � ��������.
	float probability;	// �����������

	void Show ()
	{
		std::cout << "location_id=" << location_id <<
			" start_time=" << start_time <<
			" end_time=" << end_time <<
			" min_time=" << min_time <<
			" max_time=" << max_time <<
			" probability=" << probability << std::endl;
	}
};

/*
	�������� ��� ������ ����������� ��� ������� �������� �� ����������������� �����.
*/

struct HumanConfig
{
	int human_id;
	std::list<LocationConfig> locations;
};

/*
	��������� ����������� ���� ������ � ���������.
*/
struct Period
{
	int location_id;
	time_t start_time;
	time_t end_time;
};

/*
	��������� ��������� �������� ������ ������ (���������� ������ �� �����, ������������ ���� ��� ��������).
*/
struct TimeLaps
{
	int human_id;
	std::list<Period> AllPeriods;
};

#endif