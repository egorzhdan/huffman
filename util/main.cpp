#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unarchiver.h>
#include "archiver.h"
#include "dictionary.h"

int main(int argc, char **argv) {
    if (argc != 4) {
        std::cout << "error: 4 arguments expected, " << argc << " found" << std::endl;
        return 1;
    }
    auto option = std::string(argv[1]);
    auto input_file_name = argv[2];
    auto output_file_name = argv[3];

    if (option == "archive") {

        static const std::size_t BUFFER_SIZE = 100;
        char buffer[BUFFER_SIZE];

        huffman::dictionary dict;
        std::ifstream file(input_file_name, std::ifstream::binary);

        do {
            file.read(buffer, BUFFER_SIZE);
            auto len = static_cast<std::size_t>(file.gcount());
            dict.consume_chunk(std::string(buffer, len));
        } while (file);
        file.close();

        std::ifstream is(input_file_name, std::ifstream::binary);
        std::ofstream os(output_file_name, std::ofstream::binary);

        huffman::tree tree(dict);
        huffman::archiver archiver(tree, os);
        archiver.init_output();

        do {
            is.read(buffer, BUFFER_SIZE);
            auto len = static_cast<std::size_t>(is.gcount());
            archiver.process_output(std::string(buffer, len));
        } while (is);
        archiver.finish_output();

        is.close();
        os.close();

    } else if (option == "unarchive") {

        std::ifstream is(input_file_name, std::ifstream::binary);
        std::ofstream os(output_file_name, std::ofstream::binary);

        huffman::unarchiver unarchiver(is);
        static const std::size_t BUFFER_SIZE = 100;
        std::string buffer;
        do {
            buffer = unarchiver.next_buffer(BUFFER_SIZE);
            os << buffer;
            os.flush();
        } while (!buffer.empty());

        is.close();
        os.close();

    } else {

        std::cout << "unknown option: must be 'archive' or 'unarchive'" << std::endl;
        return 1;

    }

    return 0;
}