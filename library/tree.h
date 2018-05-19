#ifndef HUFFMAN_HUFFMAN_TREE_H
#define HUFFMAN_HUFFMAN_TREE_H

#include <map>
#include "dictionary.h"
#include "binary_code.h"

namespace huffman {

    struct tree {
    public:
        explicit tree(const dictionary &dict);

        const std::map<char, binary_code> get_codes() const;

        ~tree();

    private:
        struct node {
            char symbol = 0;
            unsigned long weight = 1;
            bool represents_symbol = false;

            node *left;
            node *right;

            node(char symbol, unsigned long weight) : symbol(symbol), weight(weight), represents_symbol(true), left(nullptr), right(nullptr) {}

            node(node *left, node *right) : weight(left->weight + right->weight), left(left), right(right) {}

            ~node();
        };

        node *root;

        void traverse(node *node, binary_code cur_code, std::map<char, binary_code> &codes) const;
    };

}


#endif //HUFFMAN_HUFFMAN_TREE_H
