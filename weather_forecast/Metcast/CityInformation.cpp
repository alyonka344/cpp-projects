#include "CityInformation.h"

using json = nlohmann::json;
const std::string kMyApi = "pDk3HmnFzAGTLc1sxrlC3Q==FF8j90SRrwMwwr1K";

City::City(const std::string& name) {
    name_ = name;
    cpr::Response request = cpr::Get(cpr::Url{"https://api.api-ninjas.com/v1/city"},
                                     cpr::Header{{"X-Api-Key", kMyApi}},
                                     cpr::Parameters{{"name", name}});
    if (request.status_code == 200) {
        json data = json::parse(request.text);
        if (request.text != "[]") {
            latitude_ = data[0]["latitude"];
            longitude_ = data[0]["longitude"];
            country_ = data[0]["country"];
            SetWeather();
        }
    } else {
        throw std::runtime_error("no data connection or no internet connection");
    }
}

void City::SetWeather() {
    cpr::Response request = cpr::Get(cpr::Url{"https://api.open-meteo.com/v1/forecast"},
                                     cpr::Parameters{{"latitude",      std::to_string(latitude_)},
                                                     {"longitude",     std::to_string(longitude_)},
                                                     {"hourly",        "temperature_2m"},
                                                     {"hourly",        "windspeed_10m"},
                                                     {"hourly",        "winddirection_10m"},
                                                     {"hourly",        "relativehumidity_2m"},
                                                     {"hourly",        "weathercode"},
                                                     {"forecast_days", "10"}});

    if (request.status_code == 200) {
        json data = json::parse(request.text);
        for (int i = 0; i < data["hourly"]["time"].size();) {
            DayWeather current_day;
            current_day.date = to_string(data["hourly"]["time"][i]).substr(1, 10);
            for (int j = 0; j < 4; ++j) {
                current_day.day_weather[j].temperature = data["hourly"]["temperature_2m"][i];
                current_day.day_weather[j].wind_speed = data["hourly"]["windspeed_10m"][i];
                current_day.day_weather[j].wind_direction = data["hourly"]["winddirection_10m"][i];
                current_day.day_weather[j].humidity = data["hourly"]["relativehumidity_2m"][i];
                current_day.day_weather[j].weather_code = data["hourly"]["weathercode"][i];
                i += 6;
            }
            weather_in_city_.push_back(current_day);
        }
    } else {
        throw std::runtime_error("no data connection or no internet connection");
    }
}
