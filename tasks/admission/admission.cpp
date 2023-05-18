#include "admission.h"

#include <tuple>

const bool Comparator(const Applicant* first_applicant, const Applicant* second_applicant) {
    if (first_applicant->points == second_applicant->points) {
        return std::tie(first_applicant->student.birth_date.year, first_applicant->student.birth_date.month,
                        first_applicant->student.birth_date.day, first_applicant->student.name) <
               std::tie(second_applicant->student.birth_date.year, second_applicant->student.birth_date.month,
                        second_applicant->student.birth_date.day, second_applicant->student.name);
    } else {
        return first_applicant->points > second_applicant->points;
    }
}

AdmissionTable FillUniversities(const std::vector<University>& universities, const std::vector<Applicant>& applicants) {
    std::vector<const Applicant*> apps(applicants.size());
    for (size_t i = 0; i < applicants.size(); ++i) {
        apps[i] = &applicants[i];
    }
    std::sort(apps.begin(), apps.end(), Comparator);
    AdmissionTable admission_table(0);
    std::unordered_map<std::string, size_t> limits(universities.size());
    for (const University& university : universities) {
        admission_table[university.name] = std::vector<const Student*>();
        limits[university.name] = university.max_students;
    }
    for (const Applicant* applicant : apps) {
        for (const std::string& name : applicant->wish_list) {
            if (admission_table[name].size() < limits[name]) {
                admission_table[name].push_back(&applicant->student);
                break;
            }
        }
    }
    return admission_table;
}
