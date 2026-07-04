#include "cooking_robot.hpp"
#include <iostream>
#include <algorithm>
#include <stdexcept>

CookingRobot::CookingRobot(const std::string& id, const std::string& name,
                           int battery, const std::string& specialty)
    : Robot(id, name, battery), specialty_(specialty), meals_cooked_(0) {}

void CookingRobot::work() {
    if (battery_ == 0)
        throw std::runtime_error(name_ + " cannot work: battery is empty");
    battery_ = std::clamp(battery_ - 10, 0, 100);
    status_  = "working";
    ++meals_cooked_;
    std::cout << name_ << " cooked a " << specialty_
              << " meal. Meals today: " << meals_cooked_
              << ". Battery: " << battery_ << "%\n";
}

std::string CookingRobot::type() const { return "CookingRobot"; }
