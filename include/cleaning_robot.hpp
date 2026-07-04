#pragma once
#include "mobile_robot.hpp"
#include <string>

class CleaningRobot : public MobileRobot {
public:
    CleaningRobot(const std::string& id, const std::string& name,
                  int battery, double speed, const std::string& mode);

    void        work()  override;  // cleans area, uses 15% battery
    std::string type()  const override;

private:
    std::string mode_;  // "vacuum" , "mop" , "sweep"
};
