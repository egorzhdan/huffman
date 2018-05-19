#include <sstream>
#include <iostream>
#include <stdexcept>
#include "unarchiver.h"

huffman::unarchiver::unarchiver(std::istream &is) : ibs(is) {
    char cur_char = 0;

    bool code_expected = false; // otherwise char expected
    while (!is.eof()) {
        char cur;
        is.get(cur);

        if (!code_expected) {
            cur_char = cur;

            // skip space
            char space;
            is.get(space);
            if (cur == '\n' && space == '\n') {
                break;
            }
            if (space != ' ') throw std::runtime_error("space expected");

            code_expected = true;
        } else {
            if (cur == ' ') {
                codes[(std::size_t) (unsigned char) cur_char] = cur_code;
                cur_char = 0;
                cur_code = binary_code();

                code_expected = false;
            } else {

                switch (cur) {
                    case '0':
                        cur_code.push(false);
                        break;
                    case '1':
                        cur_code.push(true);
                        break;
                    default:
                        throw std::runtime_error("0 or 1 expected");
                }

            }
        }
    }
    cur_code = binary_code();
}

std::string huffman::unarchiver::next_buffer(const std::size_t BUFFER_MAX_SIZE) {
    if (throw_if_next) {
        throw std::runtime_error("non-existing code supplied");
    }

    std::ostringstream res;
    std::size_t length = 0;

    while (length < BUFFER_MAX_SIZE && ibs.has_more_bits()) {
        cur_code.push(ibs.next_bit());

        bool exact_char_exists = false;
        bool possible_char_exists = false;
        char possible_char = 0;
        for (std::size_t c = 0; c < dictionary::CHAR_COUNT; c++) {

            if (codes[c].starts_with(cur_code)) {
                possible_char_exists = true;
                possible_char = (unsigned char) c;
                if (cur_code.starts_with(codes[c])) {
                    exact_char_exists = true;
                    break;
                }
            }
        }

        if (exact_char_exists) {
            res << possible_char;
            length++;
            cur_code = binary_code();
        } else if (!possible_char_exists) {
            throw_if_next = true;
        }
    }
    return res.str();
}

void huffman::unarchiver::print_codes() {
    for (std::size_t c = 0; c < dictionary::CHAR_COUNT; c++) {
        std::cout << "char #" << (int) (unsigned char) c << " equals " << to_string(codes[c]) << std::endl;
    }
    std::cout << std::endl << std::endl << std::endl;
}
