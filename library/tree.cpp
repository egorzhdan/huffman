#include <queue>
#include "tree.h"

huffman::tree::tree(const dictionary &dict) {
    auto count = dict.get();

    auto comparator = [](node *a, node *b) { return a->weight > b->weight; };
    std::priority_queue<node *, std::vector<node *>, decltype(comparator)> s(comparator);

    for (const auto &p : count) {
        char c = p.first;

        if (count[c] > 0) {
            auto *cur_node = new node(c, count[c]);
            s.push(cur_node);
        }
    }

    while (s.size() > 1) {
        auto *first = s.top();
        s.pop();
        auto *second = s.top();
        s.pop();

        auto *merged = new node(first, second);
        s.push(merged);
    }

    if (!s.empty())
        root = new node(*s.top());
    else
        root = nullptr;
}

const std::map<char, huffman::binary_code> huffman::tree::get_codes() const {
    std::map<char, binary_code> res;

    if (root)
        traverse(root, binary_code(), res);

    return res;
}

void huffman::tree::traverse(node *node, binary_code cur_code, std::map<char, binary_code> &codes) const {
    if (node->represents_symbol) {
        codes[node->symbol] = binary_code(cur_code);
    } else {
        if (node->left) {
            cur_code.push(false);
            traverse(node->left, cur_code, codes);
            cur_code.pop();
        }
        if (node->right) {
            cur_code.push(true);
            traverse(node->right, cur_code, codes);
            cur_code.pop();
        }
    }
}

huffman::tree::~tree() {
    delete root;
}

huffman::tree::node::~node() {
    delete left;
    delete right;
}
