#ifndef HUFFMAN_DICTIONARY_H
#define HUFFMAN_DICTIONARY_H

#include <limits>
#include <string>
#include <map>
#include <array>

namespace huffman {

    class dictionary {
    public:
        static const std::size_t CHAR_COUNT = 256;

        void consume_chunk(const std::string &buffer);

        const std::array<unsigned long, CHAR_COUNT> &get() const;

    private:
        std::array<unsigned long, CHAR_COUNT> count = {};
    };

}

#endif //HUFFMAN_DICTIONARY_H
