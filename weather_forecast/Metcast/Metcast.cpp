#include "Metcast.h"

using json = nlohmann::json;


const int kMaxDaysInMetcast = 8;
const int kNightIndex = 0;
const int kMorningIndex = 1;
const int kDayIndex = 2;
const int kEveningIndex = 3;

std::map<int, std::string> weather_codes_ = {{0,  "Clear Sky"},
                                             {1,  "Mainly Clear"},
                                             {2,  "Partly Cloudy"},
                                             {3,  "Overcast"},
                                             {45, "Fog"},
                                             {48, "Fog"},
                                             {51, "Light Drizzle"},
                                             {53, "Moderate Drizzle"},
                                             {55, "Intensity Drizzle"},
                                             {56, "Freezing Drizzle"},
                                             {57, "Freezing Drizzle"},
                                             {61, "Slight Rain"},
                                             {63, "Moderate Rain"},
                                             {65, "Heavy Rain"},
                                             {66, "Freezing Rain"},
                                             {67, "Freezing Rain"},
                                             {71, "Slight Snowfall"},
                                             {73, "Moderate Snowfall"},
                                             {75, "Heavy Snowfall"},
                                             {77, "Snow Grains"},
                                             {80, "Rain Shower"},
                                             {81, "Rain Shower"},
                                             {82, "Rain Shower"},
                                             {85, "Snow Shower"},
                                             {86, "Snow Shower"},
                                             {95, "Thunderstorm"},
                                             {96, "Thunderstorm"},
                                             {99, "Thunderstorm"}};


std::string PartOfDay(int time) {
    switch (time) {
        case kNightIndex:
            return "Night";
        case kMorningIndex:
            return "Morning";
        case kDayIndex:
            return "Day";
        case kEveningIndex:
            return "Evening";
        default:
            return "";
    }
}

std::wstring WindDirection(int direction) {
    if (direction < 22 || direction > 337) {
        return L"↑";
    } else if (direction < 67) {
        return L"↑→";
    } else if (direction < 112) {
        return L"→";
    } else if (direction < 157) {
        return L"↓→";
    } else if (direction < 202) {
        return L"↓";
    } else if (direction < 247) {
        return L"←↓";
    } else if (direction < 292) {
        return L"←";
    } else {
        return L"←↑";
    }
}

Metcast::Metcast(const std::string& file_name) {
    std::ifstream config(file_name);
    json data = json::parse(config);
    for (int i = 0; i < data["cities"].size(); i++) {
        City current_city = City(data["cities"][i]);
        cities_.push_back(current_city);
    }
    if (data["number_of_metcast_days"] <= kMaxDaysInMetcast && data["number_of_metcast_days"] > 0) {
        default_number_days_ = data["number_of_metcast_days"];
    } else if (data["number_of_metcast_days"] > kMaxDaysInMetcast) {
        default_number_days_ = kMaxDaysInMetcast;
    } else {
        default_number_days_ = 0;
    }
}

Element Metcast::Picture(int weather_code) {
    switch (weather_code) {
        case 0:
            return vbox(text("   \\   /  "),
                        text("    .-.    "),
                        text(" ― (   ) ―"),
                        text("    \'-\'  "),
                        text("   /   \\  ")) | color(Color::Yellow2);
        case 1:
            return vbox(text("   \\  /   ") | color(Color::Yellow2),
                        hbox(text(" _ /\"\"") | color(Color::Yellow2), text(".-.") | color(Color::LightCyan1Bis)),
                        hbox(text("   \\_") | color(Color::Yellow2), text("(   ).") | color(Color::LightCyan1Bis)),
                        hbox(text("   /") | color(Color::Yellow2), text("(___(__))") | color(Color::LightCyan1Bis)));
        case 2:
            return vbox(text("   \\  /  ") | color(Color::Yellow2),
                        hbox(text(" _ /\"\"") | color(Color::Yellow2), text(".-.") | color(Color::LightSlateGrey)),
                        hbox(text("   \\") | color(Color::Yellow2), text(".(   ).") | color(Color::LightSlateGrey)),
                        hbox(text("  (____(__))") | color(Color::LightSlateGrey)));
        case 3:
            return vbox(text("     .--.   "),
                        text("  .-(    ). "),
                        text(" (___.__)__)")) | color(Color::LightCyan1Bis);
        case 45:
        case 46:
            return vbox(text(" _ - _ - _ - "),
                        text("  _ - _ - _  "),
                        text(" _ - _ - _ - ")) | color(Color::LightCyan1Bis);
        case 51:
        case 53:
        case 55:
        case 56:
        case 57:
            return vbox(text("   .-.    "),
                        text("  (   ).  "),
                        text(" (___(__) "),
                        text("  . .  . ") | color(Color::RoyalBlue1),
                        text(" .  . .") | color(Color::RoyalBlue1)) | color(Color::LightCyan1Bis);
        case 61:
        case 63:
        case 66:
        case 80:
            return vbox(text("   .-.    "),
                        text("  (   ).  "),
                        text(" (___(__) "),
                        text("  ‘ ‘ ‘ ‘ ") | color(Color::RoyalBlue1),
                        text(" ‘ ‘ ‘ ‘  ") | color(Color::RoyalBlue1)) | color(Color::LightCyan1Bis);
        case 65:
        case 67:
        case 81:
        case 82:
            return vbox(text("    .-.   "),
                        text("   (   ). "),
                        text("  (___(__)"),
                        text(" ‚‘‚‘‚‘‚‘ ") | color(Color::RoyalBlue1),
                        text(" ‚’‚’‚’‚’ ") | color(Color::RoyalBlue1)) | color(Color::LightCyan1Bis);
        case 71:
        case 73:
        case 85:
            return vbox(text("    .-.   "),
                        text("   (   ). "),
                        text("  (___(__)"),
                        text("  *  *  *") | color(Color::Cornsilk1),
                        text(" *  *  * ") | color(Color::Cornsilk1)) | color(Color::LightCyan1Bis);
        case 75:
        case 77:
        case 86:
            return vbox(text("   .-.   "),
                        text("  (   ). "),
                        text(" (___(__)"),
                        text("  * * * *") | color(Color::Cornsilk1),
                        text(" * * * * ") | color(Color::Cornsilk1)) | color(Color::LightCyan1Bis);
        case 95:
        case 96:
        case 99:
            return vbox(text("    .-.   "),
                        text("   (   ). "),
                        text("  (___(__)"),
                        hbox(text("  ‘") | color(Color::RoyalBlue1), text("/_") | color(Color::Yellow2),
                             text("‘‚") | color(Color::RoyalBlue1), text("/_") | color(Color::Yellow2),
                             text("‚") | color(Color::RoyalBlue1)),
                        hbox(text("  ’,") | color(Color::RoyalBlue1), text("/") | color(Color::Yellow2),
                             text("’,’") | color(Color::RoyalBlue1), text("/") | color(Color::Yellow2),
                             text("‚") | color(Color::RoyalBlue1))) | color(Color::LightCyan1Bis);
        default:
            return vbox(text(""));
    }
}

Element Metcast::PartOfDayMetcast(const DayWeather& current_day, int time) {
    return vbox(text(PartOfDay(time)) | center | color(Color::Plum1),
                separatorHeavy(),
                vbox(text(weather_codes_[current_day.day_weather[time].weather_code]) | center |
                     color(Color::MistyRose1),
                     hbox(Picture(current_day.day_weather[time].weather_code) | flex,
                          vbox(text(std::to_string(current_day.day_weather[time].temperature) + " °C ") |
                               align_right,
                               hbox(text(WindDirection(current_day.day_weather[time].wind_direction)) |
                                    color(Color::DeepPink2),
                                    text(std::to_string(current_day.day_weather[time].wind_speed) + " km/h ")) |
                               align_right,
                               text(std::to_string(current_day.day_weather[time].humidity) + "% ") |
                               align_right) | color(Color::RosyBrown))));
}

Element Metcast::Window(const DayWeather& current_day) {
    auto night = PartOfDayMetcast(current_day, kNightIndex);
    auto morning = PartOfDayMetcast(current_day, kMorningIndex);
    auto day = PartOfDayMetcast(current_day, kDayIndex);
    auto evening = PartOfDayMetcast(current_day, kEveningIndex);

    auto box = hbox(night | size(Direction::WIDTH, Constraint::EQUAL, 24),
                    separator(),
                    morning | size(Direction::WIDTH, Constraint::EQUAL, 24),
                    separator(),
                    day | size(Direction::WIDTH, Constraint::EQUAL, 24),
                    separator(),
                    evening | size(Direction::WIDTH, Constraint::EQUAL, 24));

    return window(text(current_day.date), box) | color(Color::HotPink3Bis) |
           size(Direction::HEIGHT, Constraint::EQUAL, 10) | size(Direction::WIDTH, Constraint::EQUAL, 100);
}

void Metcast::DefaultVector(Elements& vector, int city_number) {
    for (int i = 0; i < default_number_days_; ++i) {
        vector.push_back(Window(cities_[city_number].weather_in_city_[i]));
    }
}

void Metcast::Output() {
    auto screen = ScreenInteractive::FitComponent();

    Elements vector;
    int number_current_city = 0;

    auto config = FlexboxConfig();
    config.direction = FlexboxConfig::Direction::Column;
    config.wrap = FlexboxConfig::Wrap::Wrap;

    if (cities_.empty()) {
        throw std::runtime_error("no cities");
    }

    DefaultVector(vector, number_current_city);
    auto renderer = Renderer([&] {
        return vbox(text(cities_[number_current_city].name_ + ", " + cities_[number_current_city].country_) |
                    color(Color::IndianRed1Bis) | center |
                    borderDouble | color(Color::DeepPink4),
                    window(text(""),
                           flexbox(vector, config)) |
                    size(Direction::WIDTH, Constraint::EQUAL, 203) |
                    size(Direction::HEIGHT, Constraint::EQUAL, 45) |
                    color(Color::Black));
    });

    auto comp = CatchEvent(renderer, [&](const Event& event) {
        if (event == Event::Escape) {
            screen.ExitLoopClosure()();
            return true;
        }
        if (event == Event::Character('+')) {
            if (vector.size() < 8) {
                vector.push_back(Window(cities_[number_current_city].weather_in_city_[vector.size()]));
            }
            return true;
        }
        if (event == Event::Character('-')) {
            if (!vector.empty()) {
                vector.pop_back();
            }
            return true;
        }
        if (event == Event::Character('n')) {
            vector.clear();
            if (number_current_city + 1 < cities_.size()) {
                number_current_city++;
            } else {
                number_current_city = 0;
            }
            DefaultVector(vector, number_current_city);
            return true;
        }
        if (event == Event::Character('p')) {
            vector.clear();
            if (number_current_city > 0) {
                number_current_city--;
            } else {
                number_current_city = static_cast<int>(cities_.size()) - 1;
            }
            DefaultVector(vector, number_current_city);
            return true;
        }
        return false;
    });

    screen.Loop(comp);
}

