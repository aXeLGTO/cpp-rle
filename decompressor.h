#pragma once

#include <string>
#include <fstream>
#include <iostream>

inline bool DecodeRLE(const std::string& src_name, const std::string& dst_name) {
    using namespace std;

    ifstream in(src_name, ios::binary);
    if (!in) {
        return false;
    }

    ofstream out(dst_name, ios::binary);

    char header;
    while(in.get(header)) {
        int block_type = static_cast<unsigned char>(header) & 1;
        int data_size = (static_cast<unsigned char>(header) >> 1) + 1;

        if (block_type == 0) {
            string s(data_size, '\0');
            in.read(s.data(), data_size);
            out.write(s.data(), data_size);
        } else {
            string s(data_size, in.get());
            out.write(s.data(), data_size);
        }

    } while (in);

    return true;
}
