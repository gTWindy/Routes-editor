#include <iostream>
#include <fstream>
#include <map>
#include "Route.h"
#include "Time.h"
std::map<std::string, Route> routes;//Маршруты

void CreateRoute();
void PrintListsOfRoutes();
void OpenRoute();
void SaveRoutes();
void InitialRoutes();
std::pair<int, int> fromStrToTime(std::string str_time);
int main()
{
    setlocale(LC_ALL, "rus");
    InitialRoutes();
    std::cout << "Вводите время в формате чч:мм, пожалуйста.\n";
    std::cout << "1. Создать маршрут.\n";
    std::cout << "2. Список маршрутов.\n";
    std::cout << "3. Открыть маршрут.\n";
    std::cout << "4. Сохранить маршруты.\n";
    while (true) 
    {
        std::cout << "- ";
        int nChoice = 0;
        std::cin >> nChoice;
        switch (nChoice)
        {
        case 1:
            CreateRoute();
            break;
        case 2:
            PrintListsOfRoutes();
            break;
        case 3:
            OpenRoute();
            break;
        case 4:
            SaveRoutes();
            break;
        default:
            return 0;
        }
    }
    return 0;
}

void CreateRoute()
{
    std::cout << "Введите имя маршрута: ";
    std::string nameRoute;
    std::cin >> nameRoute;
    routes[nameRoute].CreateNewRoute();
}
void OpenRoute()
{
    std::cout << "Введите имя маршрута: ";
    std::string nameRoute;
    std::cin >> nameRoute;
    auto iter = routes.find(nameRoute);
    if (iter != routes.end())
        routes[nameRoute].PrintRoute(std::cout);
    else
        std::cout << "Такого маршрута не существует\n";
}
void PrintListsOfRoutes()
{
    int i = 1;
    for (const auto& rt : routes)
    {
        std::cout << i << ". " << rt.first << '\n';
        ++i;
    }
}
void SaveRoutes() 
{
    std::ofstream ouf;
    ouf.open("save.txt");
    
    size_t size = routes.size();
    ouf << size << std::endl;
    for(const auto& rt: routes)
    {
        ouf << rt.first <<std::endl;
        ouf << rt.second.GetCount() << std::endl;
        ouf << rt.second.Serialize();
    }
    ouf.close();
};
void InitialRoutes() 
{
    std::ifstream inf;
    inf.open("save.txt");

    size_t size;
    inf >> size;
    for(size_t i = 0; i < size; ++i)
    {
        std::string routeName;
        inf >> routeName;
        size_t count_points;
        inf >> count_points;
        
        auto rt = Route();
        rt.Deserialize(inf, count_points);
        routes[routeName] = rt;
    }
    inf.close();
}