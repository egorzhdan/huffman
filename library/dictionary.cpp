#include <iostream>
#include "dictionary.h"

void huffman::dictionary::consume_chunk(const std::string& buffer) {
    for (const char & c : buffer) {
        count[(std::size_t) (unsigned char) c]++;
    }
}

const std::array<unsigned long, huffman::dictionary::CHAR_COUNT> &huffman::dictionary::get() const {
    return count;
}
