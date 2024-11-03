#include <iostream>
#include <fstream>

/*байт на строку*/

int lines(const std::string &fileName);
int bytes(const std::string &fileName);
int words(const std::string &fileName);
int chars(const std::string &fileName);
int ex(const std::string &fileName);

int main(int argc, char **argv) {
    for (int i = 1; i <= (argc - 1); i++) {
        if (argv[i][0] != '-') {
            std::string fileName = argv[i];
            std::ifstream file(fileName, std::ios_base::in);
            if (!file) {
                std::string error = "File not found";
                std::cout << error << std::endl;
            } else {
                bool anyParametrs = false;
                for (int j = 1; j <= (argc - 1); j++) {
                    std::string option = argv[j];
                    if ((option[0] == '-') && (option[1] == '-')) {
                        if (option == "--lines") {
                            int Line = lines(fileName);
                            std::cout << Line << ' ';
                        } else if (option == "--bytes") {
                            int Byte = bytes(fileName);
                            std::cout << Byte << ' ';
                        } else if (option == "--words") {
                            int Word = words(fileName);
                            std::cout << Word << ' ';
                        } else if (option == "--chars") {
                            int Char = chars(fileName);
                            std::cout << Char << ' ';
                        }
                        anyParametrs = true;
                    } else if (option[0] == '-') {
                        bool l = false;
                        bool c = false;
                        bool w = false;
                        bool m = false;
                        for (int k = 1; k < (option.length()); k++) {
                            switch (option[k]) {
                                case 'l':
                                    if (!l) {
                                        int Line = lines(fileName);
                                        std::cout << Line << ' ';
                                        l = true;
                                    }
                                    break;
                                case 'c':
                                    if (!c) {
                                        int Byte = bytes(fileName);
                                        std::cout << Byte << ' ';
                                        c = true;
                                    }
                                    break;
                                case 'w':
                                    if (!w) {
                                        int Word = words(fileName);
                                        std::cout << Word << ' ';
                                        w = true;
                                    }
                                    break;
                                case 'm':
                                    if (!m) {
                                        int Char = chars(fileName);
                                        std::cout << Char << ' ';
                                        m = true;
                                    }
                                    break;
                            }
                        }
                        anyParametrs = true;
                    }
                }
                if (!anyParametrs) {
                    int Line = lines(fileName);
                    std::cout << Line << ' ';
//                    int Word = words(fileName);
//                    std::cout << Word << ' ';
                    int Byte = bytes(fileName);
                    std::cout << Byte << ' ';
                    int Ex = ex(fileName);
                    std::cout << Ex << ' ';
                }
                std::cout << fileName << std::endl;
            }
        }
    }
    return 0;
}

int lines(const std::string &fileName) {
    std::ifstream file(fileName, std::ios_base::in);
    size_t count = 1;
    char symbol;
    while (file) {
        symbol = file.get();
        if (symbol == '\n') {
            count++;
        }
    }
    return count;
}

int bytes(const std::string &fileName) {
    std::ifstream file(fileName, std::ios_base::in);
    size_t count = 0;
    char symbol;
    while (file) {
        symbol = file.get();
        if (symbol == '\n') {
            count += 2;
        } else if (symbol != EOF) {
            count++;
        }
    }
    return count;
}

int words(const std::string &fileName) {
    std::ifstream file(fileName, std::ios_base::in);
    size_t count = 0, words = 0;
    char symbol;
    while (file) {
        symbol = file.get();
        if (isprint(symbol) && !(isspace(symbol))) {
            count++;
        } else {
            if (count > 0) {
                words++;
                count = 0;
            }
        }
    }
    return words;
}

int chars(const std::string &fileName) {
    std::ifstream file(fileName, std::ios_base::in);
    size_t count = 0;
    char symbol;
    while (file) {
        symbol = file.get();
        if (isprint(symbol) && !(isspace(symbol))) {
            count++;
        }
    }
    return count;
}

int ex(const std::string &fileName) {
    std::ifstream file(fileName, std::ios_base::in);
    int c = bytes(fileName);
    int l = lines(fileName);
    int mean = c / l;
    return mean;
}