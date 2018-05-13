#include <cassert>
#include "ibitstream.h"
#include "bitstream.h"

void huffman::ibitstream::read_next_buffer() {
    assert(next_idx == BITS_PER_BUFFER);
    char tmp;
    if (in.get(tmp)) next_idx = 0;
    else next_idx = BITS_PER_BUFFER;

    buffer = static_cast<unsigned char>(tmp);
}

bool huffman::ibitstream::next_bit() {
    if (next_idx >= BITS_PER_BUFFER) read_next_buffer();

    return ((buffer >> (BITS_PER_BUFFER - next_idx++ - 1)) & 1) > 0; // NOLINT
}

bool huffman::ibitstream::has_more_bits() {
    if (next_idx < BITS_PER_BUFFER) return true;
    read_next_buffer();
    return (next_idx < BITS_PER_BUFFER);
}

