#include "Parser.h"

Arguments Parsing(int argc, char** argv) {
    Arguments string_parsing;
    bool one_function = true;
    for (int j = 1; j < argc; j++) {
        std::string option = argv[j];
        if (argv[j][0] != '-') {
            string_parsing.files.push_back(option);
        } else {
            if ((option == "-p" || option == "--password") && ++j < argc) {
                string_parsing.password = argv[j];
            } else if ((option == "--setpassword" || option == "-P") && ++j < argc) {
                string_parsing.password_to_set = argv[j];
            }
            if (option == "-f" && ++j < argc) {
                string_parsing.file_name = argv[j];
            } else if (option.find("--file=") != -1) {
                string_parsing.file_name = option.substr(7);
            } else if ((option == "-c" || option == "--create") && one_function) {
                std::cout << "Enter the length of the encoded word:";
                std::cin >> string_parsing.word_size;
                string_parsing.function = 0;
                one_function = false;
            } else if ((option == "-l" || option == "--list") && one_function) {
                string_parsing.function = 1;
                one_function = false;
            } else if ((option == "-x" || option == "--extract") && one_function) {
                string_parsing.function = 2;
                one_function = false;
            } else if ((option == "-a" || option == "--append") && one_function) {
                std::cout << "Enter the length of the encoded word:";
                std::cin >> string_parsing.word_size;
                string_parsing.function = 3;
                one_function = false;
            } else if ((option == "-d" || option == "--delete") && one_function) {
                string_parsing.function = 4;
                one_function = false;
            } else if ((option == "-A" || option == "--concatenate") && one_function) {
                string_parsing.function = 5;
                one_function = false;
            }
        }
    }
    return string_parsing;
}
