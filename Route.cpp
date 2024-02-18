#include <iostream>
#include "Route.h"

std::pair<int, int> fromStrToTime(std::string str_time)
{
	if (str_time.size() != 5)
		return{ 0,0 };
	int hour;
	if (str_time[0] == '0')
		hour = (str_time[1]) - 48;//'0' = 48
	else
		hour = std::atoi(str_time.substr(0, 1).c_str());

	int minutes;
	if (str_time[3] == '0')
		minutes = str_time[4] - 48;
	else
		minutes = std::atoi(str_time.substr(3, 4).c_str());

	return { hour, minutes };
}


void Route::CreateNewRoute()
{
	std::cout << "\tВведите название первого пункта: ";
	std::string namePoint, timeDepart_str;
	std::cin >> namePoint;
	std::cout << "\tИ время отправления: ";
	std::cin >> timeDepart_str;

	AddPoint(namePoint, timeDepart_str, timeDepart_str, true);//Первый пункт

	std::cout << "For the last point enter time depart like -1\n";
	while (true)
	{
		std::string namePoint, timeArrive_str, timeDepart_str;
		std::cout << "\tВведите название пункта: ";
		std::cin >> namePoint;
		std::cout << "\tВремя прибытия: ";
		std::cin >> timeArrive_str;
		std::cout << "\tВремя отправления: ";
		std::cin >> timeDepart_str;

		if (timeDepart_str == "-1")
		{
			AddPoint(namePoint, timeArrive_str, timeArrive_str, false);//Последний пункт
			break;
		}
		AddPoint(namePoint, timeArrive_str, timeDepart_str, false);
	}
}
void Route::AddPoint(std::string namePoint, std::string time_ar_str, std::string time_dp_str, bool first)
{
	std::pair<int, int> pairTimeArr = fromStrToTime(time_ar_str);
	std::pair<int, int> pairTimeDep = fromStrToTime(time_dp_str);

	Time time_arrive(pairTimeArr.first, pairTimeArr.second);
	Time time_depart(pairTimeDep.first, pairTimeDep.second);
	Point pt(namePoint, time_arrive, time_depart);

	if (first)
	{
		route.push_back(pt);
		return;
	}

	if (!InsertInRoute(pt))
		std::cout << "\tНекорректное время\n";
}
void Route::PrintRoute(std::ostream& out)
{
	out << "Начало\n";
	auto iterbefore = route.begin();
	out << iterbefore->namePoint;
	out << "\tвремя отпр.: " << (iterbefore->time_depart).str() << '\n';

	auto iter_last = route.end();
	--iter_last;

	auto iter = iterbefore;
	for (++iter; iter != route.end(); ++iter)
	{
		out << "\tвремя в пути " << (iter->time_arrive - iterbefore->time_depart).str() << '\n';
		out << iter->namePoint << '\n';
		out << "\tприб.: " << (iter->time_arrive).str() << '\n';
		if (iter != iter_last)
		{
			out << "\tотпр.: " << (iter->time_depart).str() << '\n';
			out << "вр. остановки: " << (iter->time_depart - iter->time_arrive).str() << '\n';
		}
		++iterbefore;
	}
	out << "\tобщее время в пути " << (iter_last->time_arrive - route.begin()->time_depart).str();
}
bool Route::InsertInRoute(Point pt)
{
	for (auto iter_before = route.begin(), iter_after = iter_before; iter_before != route.end(); ++iter_before)
	{
		++iter_after;

		if (pt.time_arrive <= iter_before->time_depart)
			break;//bad

		if (iter_after == route.end() || pt.time_depart <= iter_after->time_arrive)
		{
			route.insert(iter_after, pt);//good
			return "good";
		}
	}
	return "Invalid time;";//bad
}
std::string Route::Serialize() const
{
	std::string rt_str;
	auto iterStart = route.begin();
	rt_str += iterStart->namePoint + '\n';
	for (auto iter = ++route.begin(); iter != route.end(); ++iter)
	{
		rt_str += '\t' + iter->namePoint + '\n';
		rt_str += '\t' + (iter->time_arrive).str() + '\n';
		rt_str += '\t' + (iter->time_depart).str() + '\n';
	}
	return rt_str;
}
size_t Route::GetCount() const
{
	return route.size();
}
void Route::Deserialize(std::ifstream& inf, size_t count_points)
{
	std::string name, time_arr, time_dep;
	inf >> name;
	inf >> time_arr;
	inf >> time_dep;
	AddPoint(name, time_arr, time_dep, true);
	for (int j = 0; j < count_points - 1; ++j)
	{
		std::string name, time_arr, time_dep;
		inf >> name;
		inf >> time_arr;
		inf >> time_dep;
		AddPoint(name, time_arr, time_dep, false);
	}
}
