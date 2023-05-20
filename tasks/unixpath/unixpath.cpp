#include "unixpath.h"

#include <deque>
#include <sstream>

std::deque<std::string_view> AddPathToDeque(std::deque<std::string_view> current_path, std::string_view path) {
    size_t i = 0;
    size_t j = 0;
    while (j != std::string::npos) {
        j = path.find('/', i);
        std::string_view dir = path.substr(i, j - i);
        if (dir == "..") {
            if (!current_path.empty()) {
                current_path.pop_back();
            }
        } else if (dir == "." || dir.empty()) {

        } else {
            current_path.push_back(dir);
        }
        i = j;
        while (i < path.length() && path[i] == '/') {
            ++i;
        }
        if (i >= path.length() - 1) {
            break;
        }
    }
    return current_path;
}

std::string DequeToPath(std::deque<std::string_view> deque) {
    std::stringstream path;
    while (!deque.empty()) {
        path << "/" << deque.front();
        deque.pop_front();
    }
    std::string result_path = path.str();
    return result_path.empty() ? "/" : result_path;
}

std::string NormalizePath(std::string_view current_working_dir, std::string_view path) {
    std::deque<std::string_view> current_path{};
    if (path.empty()) {
        path = ".";
    }
    if (current_working_dir.empty()) {
        current_working_dir = "/";
    }
    if (path[0] == '/') {
        return DequeToPath(AddPathToDeque(current_path, path.substr(1)));
    } else {
        current_path = AddPathToDeque(current_path, current_working_dir.substr(1));
        current_path = AddPathToDeque(current_path, path);
        return DequeToPath(current_path);
    }
}
