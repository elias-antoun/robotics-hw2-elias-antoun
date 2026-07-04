#pragma once
#include "robot.hpp"
#include "task.hpp"
#include <memory>
#include <string>
#include <ostream>
#include <unordered_map>
#include <queue>

class Fleet {
public:
    void add(std::shared_ptr<Robot> robot);
    void remove(const std::string& id);
    std::shared_ptr<Robot> find(const std::string& id) const;

    // Stores the task in the priority queue and marks the robot as busy.
    void assign_task(const std::string& robot_id, const Task& t);
    void show_tasks()  const;  // prints the task queue in priority order

    void work_all()    const;  // calls work() on every robot
    void charge_all()  const;  // calls charge() on every robot

    std::size_t size()  const;
    bool        empty() const;

    Fleet& operator+=(std::shared_ptr<Robot> robot);
    Fleet& operator-=(const std::string& id);
    friend std::ostream& operator<<(std::ostream& os, const Fleet& f);

private:
    // unordered_map: O(1) average lookup by id 
    // shared_ptr: a robot can be referenced outside the fleet; unique_ptr would prevent that shared ownership.
    std::unordered_map<std::string, std::shared_ptr<Robot>> robots_;

    // priority_queue: max-heap built on a vector; top() is always the highest-priority task. Task::operator< is defined so higher value = higher rank.
    std::priority_queue<Task> tasks_;
};
