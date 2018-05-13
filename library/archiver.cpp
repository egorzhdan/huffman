#include <sstream>
#include "archiver.h"

huffman::archiver::archiver(const huffman::tree &tree, std::ostream &s) : os(s), obs(s) {
    tree_res = tree.get_codes();
}

void huffman::archiver::init_output() {
    for (const auto &p : tree_res) {
        auto it = p.second;

        os << p.first << ' ' << to_string(it) << ' ';
    }
    os << "\n\n";
}

void huffman::archiver::process_output(const std::string &buffer) {
    for (const char &c : buffer) {
        obs.append(tree_res[c]);
    }
}

void huffman::archiver::finish_output() {
    obs.flush();
}
