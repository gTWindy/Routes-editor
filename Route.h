#include "Time.h"
#include <list>
#include <fstream>
class Route
{
	class Point
	{
	public:
		Point(std::string name, Time timeAr, Time timeDp) :namePoint(name),
			time_arrive(timeAr), time_depart(timeDp) {}
	public:
		std::string namePoint;
		Time time_arrive;
		Time time_depart;
	};
public:
	Route() = default;
	~Route() = default;
	void CreateNewRoute();
	void AddPoint(std::string name, std::string time_ar, std::string time_dp, bool first);
	void PrintRoute(std::ostream& out);
	std::string Serialize() const;
	void Deserialize(std::ifstream& inf, size_t count_points);
	size_t GetCount() const;
private:
	bool InsertInRoute(Point pt);
private:
	std::list<Point> route;

};
