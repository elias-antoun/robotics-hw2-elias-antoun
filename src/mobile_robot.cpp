#include "mobile_robot.hpp"
#include <iostream>
#include <chrono>
#include <stdexcept>
#include <algorithm>  

MobileRobot::MobileRobot(const std::string& id, const std::string& name,
            int battery, double speed)
            : Robot(id, name, battery), speed_(speed) {}
void MobileRobot::work(){
    if(battery_==0)
        throw std::runtime_error(name_ + " cannot work: battery is empty");
    battery_ = std::clamp(battery_-20,0,100);
    status_ = "working";
    std::cout << name_ << " is moving at " << speed_ << " m/s. Battery: " << battery_ << "%\n";
}
std::string MobileRobot::type() const { return "MobileRobot"; }

MobileRobot::~MobileRobot() {
    stop_ = true;
    if (worker_.joinable()) worker_.join();
}

void MobileRobot::start_work(int seconds) {
    stop_ = true;                            // signal any running thread to exit its loop
    if (worker_.joinable()) worker_.join();  // wait for it to actually finish
    stop_ = false;                           // reset flag for the new thread

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