#ifndef HUFFMAN_OBITSTREAM_H
#define HUFFMAN_OBITSTREAM_H

#include <istream>
#include "bitstream.h"
#include "binary_code.h"

namespace huffman {

    class obitstream {
    public:
        explicit obitstream(std::ostream &out) : out(out) {}

        void append(bool bit);

        void append(binary_code code);

        void flush();

    private:
        std::ostream &out;

        unsigned char buffer = 0;
        std::size_t next_idx = 0;
    };

}

#endif //HUFFMAN_OBITSTREAM_H
