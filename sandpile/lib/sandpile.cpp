#include "sandpile.h"

#include <cstring>
#include <filesystem>
#include <fstream>
#include <vector>

const int32_t kBytesPerPixel = 3;

const unsigned char kWhite[3] = {255, 255, 255};
const unsigned char kGreen[3] = {0, 255, 0};
const unsigned char kViolet[3] = {255, 0, 127};
const unsigned char kYellow[3] = {0, 255, 255};
const unsigned char kBlack[3] = {0, 0, 0};

void CreateFile(const uint64_t* arr, char* image_file_name, const Arguments& input_arguments ) {
    uint32_t width_in_bytes = input_arguments.width * kBytesPerPixel;

    uint32_t padding_size = (4 - (width_in_bytes) % 4) % 4;
    unsigned char padding[padding_size];

    uint32_t stride = width_in_bytes + padding_size;

    std::filesystem::path path_to_file = input_arguments.output;
    path_to_file /= image_file_name;
    std::ofstream image_file(path_to_file);

    BitMapFileHeader file_header {0x4D42, input_arguments.length * stride + 54, 0, 0, 54};
    BitMapInfo info_header {40, input_arguments.width, input_arguments.length, 1, 24, 0, 0, 0, 0, 0, 0};

    image_file.write((char*) &file_header.bf_type, sizeof(file_header.bf_type));
    image_file.write((char*) &file_header.bf_size, sizeof(file_header.bf_size));
    image_file.write((char*) &file_header.bf_reserved1, sizeof(file_header.bf_reserved1));
    image_file.write((char*) &file_header.bf_reserved2, sizeof(file_header.bf_reserved2));
    image_file.write((char*) &file_header.bf_off_bits, sizeof(file_header.bf_off_bits));

    image_file.write((char*) &info_header.bi_size, sizeof(info_header.bi_size));
    image_file.write((char*) &info_header.bi_width, sizeof(info_header.bi_width));
    image_file.write((char*) &info_header.bi_height, sizeof(info_header.bi_height));
    image_file.write((char*) &info_header.bi_planes, sizeof(info_header.bi_planes));
    image_file.write((char*) &info_header.bi_bit_count, sizeof(info_header.bi_bit_count));
    image_file.write((char*) &info_header.bi_compression, sizeof(info_header.bi_compression));
    image_file.write((char*) &info_header.bi_size_image, sizeof(info_header.bi_size_image));
    image_file.write((char*) &info_header.bi_x_pels_per_meter, sizeof(info_header.bi_x_pels_per_meter));
    image_file.write((char*) &info_header.bi_y_pels_per_meter, sizeof(info_header.bi_y_pels_per_meter));
    image_file.write((char*) &info_header.bi_clr_used, sizeof(info_header.bi_clr_used));
    image_file.write((char*) &info_header.bi_clr_important, sizeof(info_header.bi_clr_important));

    for (size_t i = 0; i < input_arguments.length; i++) {
        for (size_t j = 0; j < input_arguments.width; j++) {
            switch (arr[i * input_arguments.width + j]) {
                case 0:
                    image_file.write((char*) &kWhite, kBytesPerPixel);
                    break;
                case 1:
                    image_file.write((char*) &kGreen, kBytesPerPixel);
                    break;
                case 2:
                    image_file.write((char*) &kViolet, kBytesPerPixel);
                    break;
                case 3:
                    image_file.write((char*) &kYellow, kBytesPerPixel);
                    break;
                default:
                    image_file.write((char*) &kBlack, kBytesPerPixel);
                    break;
            }
        }
        image_file.write((char*) &padding, padding_size);
    }
}

void SandpileModel(uint64_t* arr, Arguments input_arguments) {
    int freq = 0;
    std::string name;

    while (input_arguments.max_iter > 0) {
        std::vector<uint32_t> overflowing_cells;
        for (int i = 0; i < input_arguments.width * input_arguments.length; i++) {
            if (arr[i] >= 4) {
                overflowing_cells.push_back(i);
                arr[i] -= 4;
            }
        }

        freq++;
        for (uint64_t i = 0; i < overflowing_cells.size(); i++) {
            uint32_t top = overflowing_cells[i] - input_arguments.width;
            uint32_t bottom = overflowing_cells[i] + input_arguments.width;
            uint32_t left = overflowing_cells[i] - 1;
            uint32_t right = overflowing_cells[i] + 1;
            if (top >= 0) {
                arr[top]++;
            }
            if (bottom < input_arguments.width * input_arguments.length) {
                arr[bottom]++;
            }
            if (left >= 0 && (left % input_arguments.width) < overflowing_cells[i] % input_arguments.width) {
                arr[left]++;
            }
            if (right < input_arguments.width * input_arguments.length && (right % input_arguments.width) > overflowing_cells[i] % input_arguments.width) {
                arr[right]++;
            }
        }

        if (freq % input_arguments.freq == 0) {
            name = std::to_string(freq) + ".bmp";
            CreateFile(arr, &name[0], input_arguments);
        }

        if (overflowing_cells.empty()) {
            break;
        }

        input_arguments.max_iter--;
    }
}
