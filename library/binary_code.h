#ifndef HUFFMAN_BINARY_CODE_H
#define HUFFMAN_BINARY_CODE_H

#include <cstddef>
#include <string>
#include <vector>

namespace huffman {

    class binary_code {
    public:
        binary_code() : data(0) {}

        explicit binary_code(std::size_t size) : data(size, false) {}

        void push(bool b);

        void pop();

        std::size_t size() const;

        std::vector<bool>::const_iterator begin() const;

        std::vector<bool>::const_iterator end() const;

        bool starts_with(const binary_code &other) const;

    private:
        std::vector<bool> data;
    };

    std::string to_string(const huffman::binary_code &code);

}

#endif //HUFFMAN_BINARY_CODE_H
