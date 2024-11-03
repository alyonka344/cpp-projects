#include "archivator.h"
#include "Parser.h"
#include <fstream>

int main(int argc, char** argv) {
    Arguments string_parsing = Parsing(argc, argv);

    switch (string_parsing.function) {
        case 0:
            CreateArchive(string_parsing.file_name, string_parsing.files, string_parsing.word_size, string_parsing.password_to_set);
            break;
        case 1:
            List(string_parsing.file_name, string_parsing.password);
            break;
        case 2:
            ExtractFiles(string_parsing.file_name, string_parsing.files, string_parsing.password);
            break;
        case 3:
            Append(string_parsing.file_name, string_parsing.files[0], string_parsing.word_size, string_parsing.password);
            break;
        case 4:
            Delete(string_parsing.file_name, string_parsing.files[0], string_parsing.password);
            break;
        case 5:
            Concatenate(string_parsing.file_name, string_parsing.files[0], string_parsing.files[1]);
            break;
        default:
            if (string_parsing.password_to_set.empty()) {
                std::cerr << "no arguments";
            } else {
                SetPassword(string_parsing.file_name, string_parsing.password_to_set, string_parsing.password);
            }
            break;
    }
    return 0;
}
