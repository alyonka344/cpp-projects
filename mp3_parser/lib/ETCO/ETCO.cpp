#include "ETCO.h"

const uint16_t kSizeOfEvent = 5;
const uint16_t kSizeTimeStamp = 4;

ETCO::ETCO(std::fstream& file) : Frame(file) {
    file.read(&time_stamp_format_, kSizeOfChar);

    for (int i = 0; i < (size_ - kSizeOfChar) / kSizeOfEvent; ++i) {
        EventInfo current_event{};
        file.read(&current_event.type_of_event, kSizeOfChar);
        current_event.time_stamp = ReadingANumber(file, kSizeTimeStamp);
        events_.push_back(current_event);
    }
}

std::string ETCO::Info() const {
    std::string string_for_output = Frame::Info();
    if (time_stamp_format_ == 1) {
        string_for_output += "\nAbsolute time, 32 bit sized, using MPEG frames as unit";
    } else {
        string_for_output += "\nAbsolute time, 32 bit sized, using milliseconds as unit";
    }

    for (EventInfo event: events_) {
        string_for_output += "\nType of event: " + std::to_string((uint8_t) event.type_of_event);
        string_for_output += ", Time stamp: " + std::to_string(event.time_stamp);
    }

    return string_for_output;
}
