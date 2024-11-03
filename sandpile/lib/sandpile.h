#include <iostream>

struct BitMapFileHeader {
    uint16_t bf_type;
    uint32_t bf_size;
    uint16_t bf_reserved1;
    uint16_t bf_reserved2;
    uint32_t bf_off_bits;
};

struct BitMapInfo {
    uint32_t bi_size;
    uint32_t bi_width;
    uint32_t bi_height;
    uint16_t bi_planes;
    uint16_t bi_bit_count;
    uint32_t bi_compression;
    uint32_t bi_size_image;
    int32_t bi_x_pels_per_meter;
    int32_t bi_y_pels_per_meter;
    uint32_t bi_clr_used;
    uint32_t bi_clr_important;
};


struct Arguments {
    uint32_t length;
    uint32_t width;
    std::string input;
    std::string output;
    uint64_t max_iter;
    uint32_t freq;
};

void CreateFile(const uint64_t* arr, char* image_file_name, const Arguments& input_arguments);

void SandpileModel(uint64_t* arr, Arguments input_arguments);
