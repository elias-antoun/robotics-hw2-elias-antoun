#include "task.hpp"

// Higher priority value = higher priority so we reverse the comparison so the
// priority_queue pops the highest priority first
bool Task::operator<(const Task& other) const {
    return priority < other.priority;
}

std::ostream& operator<<(std::ostream& os, const Task& t) {
    os << "Task(\"" << t.name
       << "\", priority: " << t.priority
       << ", assigned to: " << t.assigned_to << ")";
    return os;
}
