#pragma once

#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

const int kCountPartOfDays = 4;

struct Weather {
    int temperature;
    int wind_speed;
    int humidity;
    int weather_code;
    int wind_direction;
};

struct DayWeather {
    Weather day_weather[kCountPartOfDays];
    std::string date;
};

class City {
public:
    City() = default;

    explicit City(const std::string& name);

    void SetWeather();

    std::vector<DayWeather> weather_in_city_;
    std::string name_;
    float latitude_{};
    float longitude_{};
    std::string country_;
};
