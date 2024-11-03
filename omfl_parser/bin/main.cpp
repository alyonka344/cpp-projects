#include "lib/parser.h"
#include "lib/parser_from_5_laba/ArgParser.h"

struct Options {
    bool int_var = false;
    bool string_var = false;
    bool bool_var = false;
    bool float_var = false;
    std::vector<int> array;
};

int main(int argc, char** argv) {
    Options opt;
    std::string value;
    std::string path;
    std::string default_arg;

    ArgumentParser::ArgParser ParserOMFL("Parser for laba number 6");
    ParserOMFL.AddStringArgument('f', "file", "name of OMFL file to parse").StoreValue(path);
    ParserOMFL.AddStringArgument('k', "key", "get key value").StoreValue(value);
    ParserOMFL.AddFlag("int", "output int variable").StoreValue(opt.int_var);
    ParserOMFL.AddFlag("float", "output float variable").StoreValue(opt.float_var);
    ParserOMFL.AddFlag("bool", "output bool variable").StoreValue(opt.bool_var);
    ParserOMFL.AddFlag("string", "output string variable").StoreValue(opt.string_var);
    ParserOMFL.AddIntArgument("array", "output array element").StoreValue(opt.array);
    ParserOMFL.AddStringArgument('d', "default", "if the type is specified incorrectly, then the output of the default argument").StoreValue(default_arg);
    ParserOMFL.AddHelp('h', "help", "Program parse OMFL file");

    if(!ParserOMFL.Parse(argc, argv)) {
        std::cout << "Wrong argument" << std::endl;
        std::cout << ParserOMFL.HelpDescription() << std::endl;
        return 1;
    }

    if(ParserOMFL.Help()) {
        std::cout << ParserOMFL.HelpDescription() << std::endl;
        return 0;
    }

    std::filesystem::path path_to_file = path;

    std::ifstream file(path_to_file.string());
    if (!file.is_open()) {
        std::cout << "wrong path to file";
        return 1;
    }
    const omfl::ParserOMFL root = omfl::parse(path_to_file);

    if(opt.int_var) {
        if (root.Get(value).IsInt()) {
            std::cout << "Value: " << root.Get(value).AsInt() << std::endl;
        } else if (!default_arg.empty()) {
            std::cout << "Value: " << root.Get(value).AsIntOrDefault(std::stoi(default_arg)) << std::endl;
        } else {
            std::cout << "argument isn\'t int" << std::endl;
            return 1;
        }
    } else if(opt.float_var) {
        if (root.Get(value).IsFloat()) {
            std::cout << "Value: " << root.Get(value).AsFloat() << std::endl;
        } else if (!default_arg.empty()) {
            std::cout << "Value: " << root.Get(value).AsFloatOrDefault(std::stof(default_arg)) << std::endl;
        } else {
            std::cout << "argument isn\'t float" << std::endl;
            return 1;
        }
    } else if(opt.bool_var) {
        if (root.Get(value).IsBool()) {
            std::cout << "Value: " << root.Get(value).AsBool() << std::endl;
        } else if (!default_arg.empty()) {
            bool flag = false;
            if (default_arg == "true") {
                flag = true;
            }
            std::cout << "Value: " << root.Get(value).AsBoolOrDefault(flag) << std::endl;
        } else {
            std::cout << "argument isn\'t bool" << std::endl;
            return 1;
        }
    } else if(opt.string_var) {
        if (root.Get(value).IsString()) {
            std::cout << "Value: " << root.Get(value).AsString() << std::endl;
        } else if (!default_arg.empty()) {
            std::cout << "Value: " << root.Get(value).AsStringOrDefault(default_arg) << std::endl;
        } else {
            std::cout << "argument isn\'t string" << std::endl;
            return 1;
        }
    } else if (!opt.array.empty()) {
        for (int i = 0; i < opt.array.size(); ++i) {
            if (root.Get(value)[opt.array[i]].IsBool()) {
                std::cout << "Value " << opt.array[i] << ": " << root.Get(value).AsBool() << std::endl;
            } else if (root.Get(value)[opt.array[i]].IsString()) {
                std::cout << "Value " << opt.array[i] << ": " << root.Get(value).AsString() << std::endl;
            } else if (root.Get(value)[opt.array[i]].IsInt()) {
                std::cout << "Value " << opt.array[i] << ": " << root.Get(value).AsInt() << std::endl;
            } else if (root.Get(value)[opt.array[i]].IsFloat()) {
                std::cout << "Value " << opt.array[i] << ": " << root.Get(value).AsFloat() << std::endl;
            } else {
                std::cout << "wrong argument or array";
                return 1;
            }
        }
    } else {
        if (root.Get(value).IsBool()) {
            std::cout << "Value: " << root.Get(value).AsBool() << std::endl;
        } else if (root.Get(value).IsString()) {
            std::cout << "Value: " << root.Get(value).AsString() << std::endl;
        } else if (root.Get(value).IsInt()) {
            std::cout << "Value: " << root.Get(value).AsInt() << std::endl;
        } else if (root.Get(value).IsFloat()) {
            std::cout << "Value: " << root.Get(value).AsFloat() << std::endl;
        } else {
            std::cout << "wrong argument or array";
            return 1;
        }
    }

    return 0;
}
