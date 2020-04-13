#include "StdAfx.h"
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <vector>

#include "lib_migration.h"



bool HumansConfigReader::TryAddData (std::string &data_string, HumanConfig &storage)
{
	std::istringstream iss (data_string);
	LocationConfig lc;
	std::string s;
	try 
	{
		iss >> s;
		lc.location_id = std::stoi (s);

		iss >> s; //time begin
		if (s.find(":") == std::string::npos)
			return false;
		else
		{
			s[2] = ' ';
			std::istringstream iss2 (s);
			int hour_1, min_1;
			iss2 >> hour_1 >> min_1;
			lc.start_time = hour_1 * 3600 + min_1 * 60;
		}
	
		iss >> s; //time end
		if (s.find(":") == std::string::npos)
			return false;
		else
		{
			s[2] = ' ';
			std::istringstream iss2 (s);
			int hour_2, min_2;
			iss2 >> hour_2 >> min_2;
			lc.end_time = hour_2 * 3600 + min_2 * 60;
		}

		iss >> lc.min_time;
		iss >> lc.max_time;
		iss >> lc.probability;
	} catch (...)
	{
		return false;
	}
	
	storage.locations.push_back (lc);
	//lc.Show();
	return true;
}

bool HumansConfigReader::ReadCfg()
{//Return value:
//true - ��� ������
//false - ��� �����

    std::ifstream ifs (_file_name);
    if (ifs.bad())
        return false;

	std::string s_d;
	char buf[1000];
	std::string pattern  = "[human_id=";
	HumanConfig one_human;
	one_human.human_id = -100;
	
	while (ifs)
	{
		ifs.getline(buf, sizeof(buf));
		std::string s (buf);

		int pos1 = s.find(pattern);
		if (pos1 != std::string::npos)
		{//������� ������ ����� ������ �� ��������
			//����� �� ��������
			int pos2 = s.find("]");
			if (pos2 == std::string::npos)
			{
				throw std::string ("Error in config file - can't find symbol ']'");
				return false;
			}
			pos1 += pattern.length();
			std::string s2 = s.substr( pos1, pos2 - pos1);
			int tmp_id = std::stoi (s2);
			if (one_human.human_id >= 0)
			{//��������� ����������� �������� � ������
				_humans_config.push_back (one_human);
			}

			//���������� ������������ ��� ������ ��������
			one_human.human_id = tmp_id;
			one_human.locations.clear();
		}
		else
		{
			if (TryAddData (s, one_human))
			{
				//std::cout << "Good data\n";
			}
		}

		if (!ifs)
		{//������ ������ - ��������� ������
			_humans_config.push_back (one_human);
		}
	}
	
	return true;
}


HumansMigration::HumansMigration() 
{
	srand( (unsigned)time( NULL ) ); //������������� ����� ������ �� ����� ��� � ����� �������� - ��� ������������� �����������.
	for (int i = 0; i < 7; ++i)
	{
		_humans_config.push_back(std::list <HumanConfig> ());
		_humans_time_laps.push_back (std::list<TimeLaps> ());
	}
}

bool HumansMigration::Init (const std::string file_name, int day)
{
	HumansConfigReader hcr (file_name, _humans_config[day]); //����� ����������� ������������ ������� ����� � ���������������� ��� �������
	hcr.ReadCfg();
	return true;
}

void HumansMigration::ShowConfig ()
{
	for (int i = 0; i < _humans_config.size(); ++i)
	{
		std::cout << "Size = " << _humans_config[i].size() << std::endl;
		for (auto itr = _humans_config[i].begin(); itr != _humans_config[i].end(); ++itr)
		{
			std::cout << "Human_id = " << itr->human_id << std::endl;
			for (auto itr2 = itr->locations.begin(); itr2 != itr->locations.end(); ++itr2)
			{
				itr2->Show();
			}
		}
	}
}


bool HumansMigration::MakeOneMigration (HumanConfig &human_cfg, TimeLaps &time_laps_)
{//����������� ����������� 1 ������ (������� ���������� �� ������ ������)
	TimeLaps time_laps;
	time_t cur_time = 0;
	time_laps.human_id = human_cfg.human_id;

	while (cur_time < (23 * 3600 + 59 * 60) ) //����� �����
	{
		//����� ��� �������, � ������� ������ ��������� ���������� � ��� �����
		std::vector <LocationConfig> possible_locations;
		for (auto itr_location = human_cfg.locations.begin(); itr_location != human_cfg.locations.end(); ++itr_location)
		{
			if (itr_location->start_time <=cur_time && itr_location->end_time > cur_time) //LEV!!!!! ����� ���� ��� �������� �������� �� ��, ��� ���������� ����� �� ��������� ������� ���������� ��� ���� �������
			{
				possible_locations.push_back (*itr_location); //����� ����� ������� �� �������� ����������, �� ������ �� �� �����
			}
		}

		if (possible_locations.size() == 0)
		{
			std::string err = std::string ("Can't find period for ") + std::to_string (human_cfg.human_id) + std::string (". Time is ") + std::to_string (cur_time);
			std::cout << err << std::endl;
			throw (err);
		}

		//�������� �������� ������������
		int pos_min = -1, pos = -1;
		for (int cnt = 0; cnt < 1000 && pos_min == -1; ++cnt)
		{
			for (int i = 0;  i < possible_locations.size(); ++i)
			{
				double r = (double)rand() / ((double)RAND_MAX); //LEV!!!! ����� ���� ����� ���������� �������������� ������������ � ����������� ������������� �� ����� ���������, ������ ��� ������ ����� ������ ���� �� ������� � ����� �����������.
				if (possible_locations[i].probability >= r)
				{
					pos = i;
					if (pos_min < 0)
					{
						pos_min = pos;
					}
					else
					{
						if (possible_locations[pos_min].probability > possible_locations[pos].probability)
						{//������ ������ ��������� ������� � ������� ������ �� �������
							pos_min = pos;
						}
					}
				}
			}
		}
		if (pos_min == -1)
		{//���� ����������� ������ ��� �� ���� �� ������ ������� ������ ���������� �������
			std::cout << "WARNING! Using default position!" << std::endl;
			pos_min = 0;
		}

		//��� ���������� ������� ������ ����� ���������� (�� ��� �� ����)
		int period_time = (double)rand() / (RAND_MAX + 1) * (possible_locations[pos_min].max_time - possible_locations[pos_min].min_time) + possible_locations[pos_min].min_time;
		if (cur_time + period_time > possible_locations[pos_min].end_time )
		{
			period_time = possible_locations[pos_min].end_time - cur_time;
		}

		Period per;
		per.location_id = possible_locations[pos_min].location_id;
		per.start_time = cur_time;
		per.end_time = cur_time + period_time;
		time_laps.AllPeriods.push_back (per);

		cur_time += period_time;
	}

	time_laps_ = time_laps;
	std::cout << "One migration is ready\n";
}

bool HumansMigration::MakeAllMigrations ()
{//����������� ��� ����������� �������
	for (int i = 0; i < _humans_config.size(); ++i)
	{
		for (auto itr1 = _humans_config[i].begin(); itr1 != _humans_config[i].end(); ++itr1)
		{
			TimeLaps one_agent_time_laps;
			if (MakeOneMigration (*itr1, one_agent_time_laps))
			{
				_humans_time_laps[i].push_back (one_agent_time_laps);
			}
		}
	}
	return true;
}

void HumansMigration::ShowMigration(std::string show_path)
{//�� ���������� ���� ������� �����. �� ������ �� ������� ������, � ��� �����������
	for (int i = 0; i < _humans_time_laps.size(); ++i)
	{
		for (auto itr = _humans_time_laps[i].begin(); itr != _humans_time_laps[i].end(); ++itr)
		{
			std::string file_name = show_path + "_day_" + std::to_string (i) + "_agent_id_" + std::to_string (itr->human_id);
			std::ofstream ofs (file_name);
			for (auto itr2 = itr->AllPeriods.begin(); itr2 != itr->AllPeriods.end(); ++itr2)
			{
				ofs << itr2->location_id << "\t" << itr2->start_time << "\t" << itr2->end_time << "\t" << "len=" << itr2->end_time - itr2->start_time << std::endl;
			}
		}
	}
}