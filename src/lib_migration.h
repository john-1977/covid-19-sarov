

#include "data_types.h"
#include <iostream>
#include <string>
#include <vector>

class HumansConfigReader
{
public:
	HumansConfigReader (const std::string &file_name, std::list <HumanConfig> &humans_config ) : _file_name  (file_name), _humans_config(humans_config)
	{
		 
	}
	bool TryAddData (std::string &data_string, HumanConfig &storage);
	bool ReadCfg();

private:
	const std::string &_file_name;
	std::list <HumanConfig> &_humans_config;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




/*
 ����� ����������� �������� ����� ����� ��������� �� ��������� ����������������� �����.
*/
class HumansMigration
{
public:
	HumansMigration();
	bool Init (const std::string file_name, int day);
	void ShowConfig ();

	bool MakeAllMigrations (); //����������� ��� ����������� �������
	bool MakeOneMigration (HumanConfig &human_cfg, TimeLaps &time_laps_); //����������� ����������� 1 ������ (������� ���������� �� ������ ������)
	void ShowMigration(std::string show_path); //�� ���������� ���� ������� �����. �� ������ �� ������� ������, � ��� �����������

protected:
	//std::list <HumanConfig> _humans_config_0; //������������ �� ���� �����
	//std::list<TimeLaps> _humans_time_laps_0; // �������������� ������ - ���������� ���� ������� �� �����
	std::vector<std::list <HumanConfig> > _humans_config; //������������ �� ���� ����� �� ���� ���� (0 - �����������, 1 - �������, ..., 6 - �����������)
	std::vector<std::list<TimeLaps> > _humans_time_laps; // �������������� ������ - ���������� ���� ������� �� �����
};