#ifndef HUFFMAN_IBITSTREAM_H
#define HUFFMAN_IBITSTREAM_H

#include <cstddef>
#include <climits>
#include <iosfwd>
#include <istream>
#include "bitstream.h"

namespace huffman {

    class ibitstream {
    public:
        explicit ibitstream(std::istream &in) : in(in) {}

        bool next_bit();

        bool has_more_bits();

    private:
        std::istream &in;

        char buffer = 0;
        std::size_t next_idx = BITS_PER_BUFFER;

        void read_next_buffer();
    };

}

#endif //HUFFMAN_IBITSTREAM_H
