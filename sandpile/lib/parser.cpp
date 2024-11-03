#include "parser.h"

#include <fstream>

void OpenTSV(uint64_t* arr, const Arguments& input_arguments) {
    std::ifstream input_file(input_arguments.input, std::ios_base::in);

    while(input_file) {
        uint32_t coordinate_x;
        uint32_t coordinate_y;
        uint64_t count;
        input_file >> coordinate_x >> coordinate_y >> count;

        arr[coordinate_y * input_arguments.width + coordinate_x] = count;
    }
}

void Parsing(int argc, char** argv) {
    Arguments input_arguments;
    bool first_input_l = true;
    bool first_input_w = true;
    bool first_input_i = true;
    bool first_input_o = true;
    bool first_input_m = true;
    bool first_input_f = true;

    for (int j = 1; j < argc; j++) {
        std::string option = argv[j];
        if (argv[j][0] == '-') {
            if ((option == "-l" || option == "--length") && first_input_l) {
                input_arguments.length = std::stoi(argv[++j]);
                first_input_l = false;
            } else if ((option == "-w" || option == "--width") && first_input_w) {
                input_arguments.width = std::stoi(argv[++j]);
                first_input_w = false;
            } else if ((option == "-i" || option == "--input") && first_input_i) {
                input_arguments.input = argv[++j];
                first_input_i = false;
            } else if ((option == "-o" || option == "--output") && first_input_o) {
                input_arguments.output = argv[++j];
                first_input_o = false;
            } else if ((option == "-m" || option == "--max-iter") && first_input_m) {
                input_arguments.max_iter = std::stoi(argv[++j]);
                first_input_m = false;
            } else if ((option == "-f" || option == "--freq") && first_input_f) {
                input_arguments.freq = std::stoi(argv[++j]);
                first_input_f = false;
            }
        }
    }

    uint64_t* arr = new uint64_t[input_arguments.width * input_arguments.length];
    for (int j = 0; j < input_arguments.width * input_arguments.length; j++) {
        arr[j] = 0;
    }

    OpenTSV(arr, input_arguments);
    SandpileModel(arr, input_arguments);

    delete[] arr;
}