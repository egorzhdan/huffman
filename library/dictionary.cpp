#include <iostream>
#include "dictionary.h"

void huffman::dictionary::consume_chunk(const std::string& buffer) {
    for (const char & c : buffer) {
        count[c]++;
    }
}

const std::map<char, unsigned long> &huffman::dictionary::get() const {
    return count;
}
