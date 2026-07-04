#pragma once
#include "robot.hpp"
#include <string>

class CookingRobot : public Robot {
public:
    CookingRobot(const std::string& id, const std::string& name,
                 int battery, const std::string& specialty);

    void work()  override;  // cooks one meal, uses 10% battery
    std::string type()  const override;

private:
    std::string specialty_;    // cuisine type example "Italian"
    int meals_cooked_;
};
