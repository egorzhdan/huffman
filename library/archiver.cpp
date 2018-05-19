#include <sstream>
#include "archiver.h"

huffman::archiver::archiver(const huffman::tree &tree, std::ostream &s) : os(s), obs(s) {
    tree_res = tree.get_codes();
    for (auto p : tree_res) {
        bool all_zero = true;
        for (bool it : p.second) {
            if (it) all_zero = false;
        }

        if (all_zero)
            tree_res[p.first].push(true);
    }
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
