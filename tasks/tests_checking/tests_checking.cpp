#include "tests_checking.h"

#include <deque>

std::vector<std::string> StudentsOrder(const std::vector<StudentAction>& student_actions,
                                       const std::vector<size_t>& queries) {
    std::deque<std::string> deque;
    for (const auto& student_action : student_actions) {
        if (student_action.side == Side::Top) {
            deque.push_front(student_action.name);
        }
        else {
            deque.push_back(student_action.name);
        }
    }
    std::vector<std::string> names{};
    for (const auto& index : queries) {
        names.push_back(deque[index - 1]);
    }
    return names;
}
