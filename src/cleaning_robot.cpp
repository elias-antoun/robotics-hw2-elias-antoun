#include "cleaning_robot.hpp"
#include <iostream>
#include <algorithm> 
#include <stdexcept>

CleaningRobot::CleaningRobot(const std::string& id, const std::string& name,
                             int battery, double speed, const std::string& mode)
    : MobileRobot(id, name, battery, speed), mode_(mode) {}

void CleaningRobot::work() {
    if (battery_ == 0)
        throw std::runtime_error(name_ + " cannot work: battery is empty");
    battery_ = std::clamp(battery_ - 15, 0, 100);
    status_  = "working";
    std::cout << name_ << " is cleaning in " << mode_
              << " mode at " << speed_ << " m/s. Battery: " << battery_ << "%\n";
}

std::string CleaningRobot::type() const { return "CleaningRobot"; }
