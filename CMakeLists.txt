cmake_minimum_required(VERSION 3.10)
project(Huffman)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++20 -pedantic")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined -D_GLIBCXX_DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")

add_library(huffman STATIC
        library/tree.cpp library/tree.h
        library/dictionary.cpp library/dictionary.h
        library/archiver.cpp library/archiver.h
        library/binary_code.cpp library/binary_code.h
        library/ibitstream.cpp library/ibitstream.h
        library/obitstream.cpp library/obitstream.h
        library/bitstream.h library/unarchiver.cpp library/unarchiver.h)

include_directories(library)

add_executable(huffmanutil
        util/main.cpp)
target_link_libraries(huffmanutil huffman)

add_executable(huffman-test
        test/gtest/gtest-all.cc
        test/gtest/gtest.h
        test/gtest/gtest_main.cc
        test/tests.cpp)
target_link_libraries(huffman-test huffman)