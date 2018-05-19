#include "obitstream.h"

void huffman::obitstream::flush() {
    out.put(buffer);
    buffer = 0;
    next_idx = 0;
}

void huffman::obitstream::append(bool bit) {
    if (next_idx == BITS_PER_BUFFER) flush();

    buffer |= (bit << (BITS_PER_BUFFER - next_idx++ - 1));
}

void huffman::obitstream::append(const huffman::binary_code& code) {
    for (const auto &it : code) {
        append(it);
    }
}
