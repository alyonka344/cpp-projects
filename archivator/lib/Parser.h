#include <iostream>
#include <vector>

struct Arguments {
    int function;
    int word_size;
    std::string file_name;
    std::vector<std::string> files;
    std::string password;
    std::string password_to_set;

    Arguments() {
        function = 6;
        word_size = 0;
    }
};

Arguments Parsing(int argc, char** argv);
