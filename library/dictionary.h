#ifndef HUFFMAN_DICTIONARY_H
#define HUFFMAN_DICTIONARY_H

#include <limits>
#include <string>
#include <map>
#include <array>

namespace huffman {

    class dictionary {
    public:
        static const std::size_t CHAR_COUNT = (std::size_t) std::numeric_limits<unsigned char>::max() + 1;

        void consume_chunk(const std::string &buffer);

        const std::map<char, unsigned long> &get() const;

    private:
        std::map<char, unsigned long> count = {};
    };

}

#endif //HUFFMAN_DICTIONARY_H
