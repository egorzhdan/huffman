#ifndef HUFFMAN_ARCHIVER_H
#define HUFFMAN_ARCHIVER_H

#include "dictionary.h"
#include "tree.h"
#include "obitstream.h"

namespace huffman {

    class archiver {
    public:
        explicit archiver(const tree &tree, std::ostream &s);

        void init_output();

        void process_output(const std::string &buffer);

        void finish_output();

    private:
        std::ostream &os;
        obitstream obs;
        std::map<char, huffman::binary_code> tree_res;
    };

}

#endif //HUFFMAN_ARCHIVER_H
