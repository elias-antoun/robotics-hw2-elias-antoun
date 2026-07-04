#include "robot.hpp"
#include <algorithm>  // for std::clamp
#include <stdexcept>

Robot::Robot(const std::string& id, const std::string& name, int battery)
    : id_(id), name_(name), battery_(std::clamp(battery, 0, 100)), status_("idle") {}

void Robot::charge() {
    battery_ = 100;
    status_  = "charging";
}

std::string Robot::id() const { return id_; }
std::string Robot::name() const { return name_; }
int Robot::battery() const { return battery_; }
std::string Robot::status() const { return status_; }

bool Robot::operator==(const Robot& other) const {
    return id_ == other.id_;
}

std::string Robot::operator+(const Robot& other) const {
    return name_ + " + " + other.name_;
}

// friend: operator<< must be a free function because the left operand is std::ostream, not Robot, so it cannot be a member of Robot.
// Declared friend so it can access private members (id_, name_,...) without being part of the class.
std::ostream& operator<<(std::ostream& os, const Robot& r) {
    os << "[" << r.type() << "] " << r.name_
       << " (id: " << r.id_
       << ", battery: " << r.battery_ << "%"
       << ", status: " << r.status_ << ")";
    return os;
}
