#include "fleet.hpp"
#include <iostream>
#include <algorithm> 
#include <stdexcept>

void Fleet::add(std::shared_ptr<Robot> robot) {
    robots_[robot->id()] = robot;
}

void Fleet::remove(const std::string& id) {
    if (robots_.erase(id) == 0)
        throw std::runtime_error("Cannot remove: robot not found: " + id);
}

std::shared_ptr<Robot> Fleet::find(const std::string& id) const {
    auto it = robots_.find(id);
    if (it == robots_.end())
        throw std::runtime_error("Robot not found: " + id);
    return it->second;
}

void Fleet::assign_task(const std::string& robot_id, const Task& t) {
    find(robot_id);  // throws if robot doesn't exist
    tasks_.push(t);
    std::cout << "Task \"" << t.name << "\" (priority " << t.priority
              << ") assigned to " << robot_id << "\n";
}

void Fleet::show_tasks() const {
    if (tasks_.empty()) {
        std::cout << "No tasks in queue.\n";
        return;
    }
    // priority_queue doesn't support iteration — copy it and pop in order
    auto copy = tasks_;
    while (!copy.empty()) {
        std::cout << "  " << copy.top() << "\n";
        copy.pop();
    }
}

void Fleet::work_all() const {
    // Warn about any dead-battery robot
    auto it = std::find_if(robots_.begin(), robots_.end(),
        [](const auto& pair) { return pair.second->battery() == 0; });
    if (it != robots_.end())
        std::cout << "Warning: " << it->second->name() << " has no battery.\n";

    for (const auto& [id, robot] : robots_) {
        try {
            robot->work();
        } catch (const std::runtime_error& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }
}

void Fleet::charge_all() const {
    for (const auto& [id, robot] : robots_)
        robot->charge();
    std::cout << "All robots charged to 100%.\n";
}

std::size_t Fleet::size()  const { return robots_.size(); }
bool Fleet::empty() const { return robots_.empty(); }

Fleet& Fleet::operator+=(std::shared_ptr<Robot> robot) {
    add(robot);
    return *this;
}

Fleet& Fleet::operator-=(const std::string& id) {
    remove(id);
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Fleet& f) {
    os << "Fleet (" << f.robots_.size() << " robots):\n";
    for (const auto& [id, robot] : f.robots_)
        os << "  " << *robot << "\n";
    return os;
}
