#pragma once

#include "CityInformation.h"

#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "nlohmann/json.hpp"

#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

using namespace ftxui;

class Metcast {
public:
    explicit Metcast(const std::string& file_name);
    void Output();

private:
    static Element PartOfDayMetcast(const DayWeather& current_day, int time);
    static Element Picture(int weather_code);
    static Element Window(const DayWeather& current_day);
    void DefaultVector(Elements& vector, int city_number);
    std::vector<City> cities_;
    int default_number_days_{};
};
