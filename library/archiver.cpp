#include <sstream>
#include "archiver.h"

huffman::archiver::archiver(const huffman::tree &tree, std::ostream &s) : os(s), obs(s) {
    tree_res = tree.get_codes();
    for (std::size_t c = 0; c < huffman::dictionary::CHAR_COUNT; c++) {
        auto p = tree_res[c];

        bool all_zero = true;
        for (bool it : p) {
            if (it) all_zero = false;
        }

        if (all_zero)
            tree_res[c].push(true);
    }
}

void huffman::archiver::init_output() {
    for (std::size_t c = 0; c < huffman::dictionary::CHAR_COUNT; c++) {
        auto it = tree_res[c];

        os << (char) c << ' ' << to_string(it) << ' ';
    }
    os << "\n\n";
}

void huffman::archiver::process_output(const std::string &buffer) {
    for (const char &c : buffer) {
        obs.append(tree_res[(std::size_t) (unsigned char) c]);
    }
}

void huffman::archiver::finish_output() {
    obs.flush();
}
