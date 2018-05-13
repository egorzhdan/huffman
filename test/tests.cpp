#include "gtest/gtest.h"
#include "dictionary.h"
#include "tree.h"
#include "archiver.h"
#include "unarchiver.h"

using namespace std;

string archive(const string &src, size_t buf_size = 1000) {
    huffman::dictionary dict;
    for (size_t i = 0; i < src.length(); i += buf_size) {
        dict.consume_chunk(src.substr(i, buf_size));
    }

    ostringstream os;

    huffman::tree tree(dict);
    huffman::archiver archiver(tree, os);

    archiver.init_output();
    archiver.process_output(src);
    archiver.finish_output();

    return os.str();
}

string unarchive(const string &archive, size_t buf_size = 1000) {
    string unpacked, buffer;
    istringstream is = istringstream(archive);
    huffman::unarchiver unarchiver(is);
    unarchiver.print_codes();
    do {
        buffer = unarchiver.next_buffer(buf_size);
        unpacked.append(buffer);
    } while (buffer.length() > 0);
    return unpacked;
}


TEST(plain_text, alphanumeric) {
    string alpha;
    for (char i = 'a'; i <= 'z'; i++) {
        alpha.push_back(i);
    }
    for (char i = 'A'; i <= 'Z'; i++) {
        alpha.push_back(i);
        alpha.push_back(i);
    }
    for (char i = '0'; i <= '9'; i++) {
        alpha.push_back(i);
    }

    string packed = archive(alpha, 20);
    string unpacked = unarchive(packed, 20);

    ASSERT_EQ(alpha, unpacked);
}

TEST(plain_text, whitespace) {
    string alpha;
    for (char c = 0; c < CHAR_MAX; c++) {
        if (isspace(c)) alpha.push_back(c);
    }

    string packed = archive(alpha, 20);
    string unpacked = unarchive(packed, 20);

    ASSERT_EQ(alpha, unpacked);
}

TEST(plain_text, all) {
    string alpha;
    for (char c = CHAR_MIN; c < CHAR_MAX; c++) {
        alpha.push_back(c);
    }

    string packed = archive(alpha, 100);
    string unpacked = unarchive(packed, 100);

    ASSERT_EQ(alpha, unpacked);
}