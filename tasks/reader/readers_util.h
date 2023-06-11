#pragma once

#include <algorithm>
#include <memory>
#include <utility>
#include <vector>

#include "reader.h"

const int TEN = 10;

class LimitReader : public Reader {
public:
    LimitReader(std::unique_ptr<Reader> reader, size_t limit) {
        reader_.swap(reader);
        limit_ = limit;
    }

    size_t Read(char* buf, size_t len) override {
        size_t max_read = std::min(len, limit_);
        size_t ret = reader_->Read(buf, max_read);
        limit_ -= ret;
        return ret;
    }

private:
    std::unique_ptr<Reader> reader_;
    size_t limit_;
};

class TeeReader : public Reader {
public:
    explicit TeeReader(std::vector<std::unique_ptr<Reader>> readers) {
        readers_.swap(readers);
        current_ = 0;
    }

    size_t Read(char* buf, size_t len) override {
        while (true) {
            if (current_ == readers_.size()) {
                return 0;
            }
            size_t ret = readers_[current_]->Read(buf, len);
            if (ret == 0) {
                ++current_;
                continue;
            }
            return ret;
        }
    }

private:
    std::vector<std::unique_ptr<Reader>> readers_;
    size_t current_;
};

class HexDecodingReader : public Reader {
public:
    explicit HexDecodingReader(std::unique_ptr<Reader> reader) {
        reader_.swap(reader);
    }

    size_t Read(char* buf, size_t len) override {
        std::string raw(len * 2, '\0');
        size_t read_len = reader_->Read(&(raw[0]), raw.size());
        for (size_t i = 0; i < read_len; i += 2) {
            int c1 = '0' <= raw[i] && raw[i] <= '9' ? raw[i] - '0' : raw[i] - 'A' + TEN;
            int c2 = '0' <= raw[i + 1] && raw[i + 1] <= '9' ? raw[i + 1] - '0' : raw[i + 1] - 'A' + TEN;
            buf[i / 2] = static_cast<char>((c1 << 4) | c2);
        }
        return read_len / 2;
    }

private:
    std::unique_ptr<Reader> reader_;
};
