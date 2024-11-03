#include "FileParser.h"

void Parser::ParseFrames() {
    std::fstream file(path_to_file_, std::ios_base::binary | std::ios_base::in);

    if (!file.is_open()) {
        std::cout << "File not found.";
        return;
    }

    Header header(file);

    while (file.tellg() < header.Size()) {
        char symbol;
        std::string id;
        for (int i = 0; i < kIDLength; i++) {
            file.read(&symbol, 1);
            id += symbol;
        }

        Frame* current_frame;

        if (id[0] == 'T') {
            current_frame = new TextFrame(file);
        } else if (id[0] == 'W') {
            current_frame = new URLFrame(file);
        } else if (id == "COMM") {
            current_frame = new COMM(file);
        } else if (id == "UFID") {
            current_frame = new UFID(file);
        } else if (id == "USER") {
            current_frame = new USER(file);
        } else if (id == "USLT") {
            current_frame = new USLT(file);
        } else if (id == "ENCR") {
            current_frame = new ENCR(file);
        } else if (id == "GRID") {
            current_frame = new GRID(file);
        } else if (id == "LINK") {
            current_frame = new LINK(file);
        } else if (id == "OWNE") {
            current_frame = new OWNE(file);
        } else if (id == "PRIV") {
            current_frame = new PRIV(file);
        } else if (id == "POPM") {
            current_frame = new POPM(file);
        } else if (id == "POSS") {
            current_frame = new POSS(file);
        } else if (id == "PCNT") {
            current_frame = new PCNT(file);
        } else if (id == "SEEK") {
            current_frame = new SEEK(file);
        } else if (id == "COMR") {
            current_frame = new COMR(file);
        } else if (id == "RBUF") {
            current_frame = new RBUF(file);
        } else if (id == "ETCO") {
            current_frame = new ETCO(file);
        } else if (id == "SYLT") {
            current_frame = new SYLT(file);
        } else if (id[0] == '\0') {
            break;
        } else {
            current_frame = new Frame(file);
            std::cout << "This frame is not supported. " << *current_frame;
            file.seekg(current_frame->Size(), std::ios::cur);
            continue;
        }

        std::cout << *current_frame;

        delete current_frame;
    }
    file.close();
}

void Parser::Parse(int argc, char** argv) {
    for (int i = 1; i < argc; ++i) {
        std::string option = argv[i];
        if ((option == "--file" || option == "-f") && i + 1 < argc) {
            path_to_file_ = argv[++i];
            std::cout << "File: " << path_to_file_ << '\n';
            ParseFrames();
        } else {
            std::cout << "Wrong option.\nEnter as:\n-f <filename>\nOr:\n--file <filename>";
            ++i;
        }
    }
}
