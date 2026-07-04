#include "mobile_robot.hpp"
#include <iostream>
#include <chrono>
#include <stdexcept>
#include <algorithm>  

MobileRobot::MobileRobot(const std::string& id, const std::string& name,
            int battery, double speed);
            : Robot(id,name,battery), speed_(speed) {}
void MobileRobot::work(){
    if(battery_==0)
        throw std::runtime_error(name_ + " cannot work: battery is empty");
    battery_ = std::clamp(battery_-20,0,100);
    status_ = "working";
    std::cout << name_ << " is moving at " << speed_ << " m/s. Battery: " << battery_ << "%\n";
}
std::string MobileRobot::type()  const {return "MobileRobot";}

void MobileRobot::start_work(int seconds);

void MobileRobot::start_work(int seconds) {
    stop_ = false;
    // Join any previous thread before launching a new one
    if (worker_.joinable()) worker_.join();

    worker_ = std::thread([this, seconds]() {
        for (int i = 0; i < seconds && !stop_; ++i) {
            try {
                work();
            } catch (const std::runtime_error& e) {
                std::cout << "Error: " << e.what() << "\n";
                break;
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });
}