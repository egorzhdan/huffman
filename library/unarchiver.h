#ifndef HUFFMAN_UNARCHIVER_H
#define HUFFMAN_UNARCHIVER_H

#include <istream>
#include <map>
#include <vector>
#include <string>
#include "binary_code.h"
#include "ibitstream.h"
#include "dictionary.h"

namespace huffman {

    class unarchiver {
    public:
        unarchiver() = delete;

        explicit unarchiver(std::istream &is);

        std::string next_buffer(std::size_t BUFFER_MAX_SIZE);

        void print_codes();

    private:
        ibitstream ibs;
        binary_code cur_code;
        bool throw_if_next = false;

        std::array<binary_code, dictionary::CHAR_COUNT> codes;
    };

}

#endif //HUFFMAN_UNARCHIVER_H
