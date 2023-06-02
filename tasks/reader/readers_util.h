#pragma once

#include <memory>
#include <vector>

#include "reader.h"

class LimitReader : public Reader {
public:
    LimitReader(std::unique_ptr<Reader> reader, size_t limit) {
        reader_.swap(reader);
        limit_ = limit;
    }

    virtual size_t Read(char* buf, size_t len) override {
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
    TeeReader(std::vector<std::unique_ptr<Reader>> readers) {
        readers_.swap(readers);
        current_ = 0;
    }

    virtual size_t Read(char* buf, size_t len) {
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

char Hex2num(char c) {
    if ('0' <= c && c <= '9') {
        return c - '0';
    }
    return c - 'A' + 10;
}

class HexDecodingReader : public Reader {
public:
    HexDecodingReader(std::unique_ptr<Reader> reader) {
        reader_.swap(reader);
    }

    virtual size_t Read(char* buf, size_t len) {
        std::string raw(len * 2, '\0');
        size_t read_len = reader_->Read(&(raw[0]), raw.size());
        for (size_t i = 0; i < read_len; i += 2) {
            buf[i / 2] = (Hex2num(raw[i] << 4)) | Hex2num(raw[i + 1]);
        }
        return read_len / 2;
    }

private:
    std::unique_ptr<Reader> reader_;
};