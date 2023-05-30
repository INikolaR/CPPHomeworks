#include "scorer.h"

#include <vector>

bool Comparator(const Event*& first_event, const Event*& second_event) {
    return first_event->time < second_event->time;
}

ScoreTable GetScoredStudents(const Events& events, time_t score_time) {
    std::vector<const Event*> sorted_events(events.size());
    size_t index = 0;
    for (const auto& event : events) {
        sorted_events[index++] = &event;
    }
    std::sort(sorted_events.begin(), sorted_events.end(), Comparator);
    ScoreTable completed_tasks{};
    std::map<StudentName, std::set<TaskName>> opened_merge_requests{};
    std::set<StudentName> students{};
    for (const auto& event : sorted_events) {
        if (event->time > score_time) {
            continue;
        }
        students.insert(event->student_name);
        switch (event->event_type) {
            case EventType::CheckFailed:
                completed_tasks[event->student_name].erase(event->task_name);
                break;
            case EventType::CheckSuccess:
                completed_tasks[event->student_name].insert(event->task_name);
                break;
            case EventType::MergeRequestOpen:
                opened_merge_requests[event->student_name].insert(event->task_name);
                break;
            case EventType::MergeRequestClosed:
                opened_merge_requests[event->student_name].erase(event->task_name);
                break;
            default:
                break;
        }
    }
    for (const auto& student : students) {
        for (const auto& task : opened_merge_requests[student]) {
            completed_tasks[student].erase(task);
        }
        if (completed_tasks[student].empty()) {
            completed_tasks.erase(student);
        }
    }
    return completed_tasks;
}
