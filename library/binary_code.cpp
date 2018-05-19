#include <sstream>
#include <stdexcept>
#include "binary_code.h"

void huffman::binary_code::push(bool b) {
    data.push_back(b);
}

void huffman::binary_code::pop() {
    data.pop_back();
}

std::size_t huffman::binary_code::size() const {
    return data.size();
}

std::vector<bool>::const_iterator huffman::binary_code::begin() const {
    return data.begin();
}

std::vector<bool>::const_iterator huffman::binary_code::end() const {
    return data.end();
}

bool huffman::binary_code::starts_with(const huffman::binary_code &other) const {
    if (other.size() > size()) return false;

    for (std::size_t i = 0; i < other.size(); i++) {
        if (data[i] != other.data[i]) return false;
    }
    return true;
}

std::string huffman::to_string(const huffman::binary_code &code) {
    std::ostringstream res;

    if (code.size() == 0) res << 'n';
    else for (const auto &it : code) res << it;

    return res.str();
}
