#include "sort_students.h"

#include <algorithm>

bool operator==(Date date1, Date date2) {
    return date1.year == date2.year && date1.month == date2.month && date1.day == date2.day;
}

bool operator<(Date date1, Date date2) {
    if (date1.year == date2.year) {
        if (date1.month == date2.month) {
            return date1.day < date2.day;
        }
        return date1.month < date2.month;
    }
    return date1.year < date2.year;
}

void SortStudents(std::vector<Student>& students, SortKind sort_kind) {
    if (sort_kind == SortKind::Date) {
        std::sort(students.begin(), students.end(), [](Student a, Student b) {
            if (a.birth_date == b.birth_date) {
                if (a.last_name == b.last_name) {
                    return a.name < b.name;
                }
                return a.last_name < b.last_name;
            }
            return a.birth_date < b.birth_date;
        });
    } else {
        std::sort(students.begin(), students.end(), [](Student a, Student b) {
            if (a.last_name == b.last_name) {
                if (a.name == b.name) {
                    return a.birth_date < b.birth_date;
                }
                return a.name < b.name;
            }
            return a.last_name < b.last_name;
        });
    }
}
