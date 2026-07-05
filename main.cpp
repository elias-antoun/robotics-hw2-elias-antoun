#include <iostream>
#include <memory>
#include <string>
#include <limits>
#include "fleet.hpp"
#include "mobile_robot.hpp"
#include "cleaning_robot.hpp"
#include "cooking_robot.hpp"
#include "task.hpp"

// reads an int in [min, max], loops on bad input
int readInt(const std::string& prompt, int min, int max) {
    int val;
    while (true) {
        std::cout << prompt;
        if (std::cin >> val && val >= min && val <= max)
            return val;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Enter a number between " << min << " and " << max << ": \n";
    }
}

double readDouble(const std::string& prompt) {
    double val;
    while (true) {
        std::cout << prompt;
        if (std::cin >> val && val > 0) return val;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Enter a positive number: ";
    }
}

std::string readWord(const std::string& prompt) {
    std::string s;
    std::cout << prompt;
    std::cin >> s;
    return s;
}

void addRobot(Fleet& fleet) {
    std::cout << "  1. MobileRobot\n"
              << "  2. CleaningRobot\n"
              << "  3. CookingRobot\n";
    int type = readInt("Type: ", 1, 3);
    std::string id = readWord("ID: ");
    std::string name = readWord("Name: ");
    int battery = readInt("Battery (0-100): ", 0, 100);

    try {
        switch (type) {
            case 1: {
                double speed = readDouble("Speed (m/s): ");
                fleet.add(std::make_shared<MobileRobot>(id, name, battery, speed));
                break;
            }
            case 2: {
                double speed = readDouble("Speed (m/s): ");
                std::string mode = readWord("Mode (vacuum/mop/sweep): ");
                fleet.add(std::make_shared<CleaningRobot>(id, name, battery, speed, mode));
                break;
            }
            case 3: {
                std::string specialty = readWord("Specialty (e.g. Italian): ");
                fleet.add(std::make_shared<CookingRobot>(id, name, battery, specialty));
                break;
            }
        }
        std::cout << "Robot added successfully.\n";
    } catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void removeRobot(Fleet& fleet) {
    std::string id = readWord("Robot ID to remove: ");
    try {
        fleet.remove(id);
        std::cout << "Robot removed.\n";
    } catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void workSingle(Fleet& fleet) {
    std::string id = readWord("Robot ID: ");
    try {
        fleet.find(id)->work();
    } catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void assignTask(Fleet& fleet) {
    std::string id = readWord("Robot ID: ");
    std::string taskName = readWord("Task name: ");
    int priority = readInt("Priority (1-5): ", 1, 5);
    try {
        fleet.assign_task(id, Task{taskName, priority, id});
    } catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void startTimedWork(Fleet& fleet) {
    std::string id = readWord("Robot ID: ");
    int seconds = readInt("Duration (1-60 seconds): ", 1, 60);
    try {
        auto robot = fleet.find(id);
        auto* mobile = dynamic_cast<MobileRobot*>(robot.get());
        if (!mobile) {
            std::cout << "Error: " << id << " is not a MobileRobot.\n";
            return;
        }
        mobile->start_work(seconds);
        std::cout << "Background work started for " << seconds << "s.\n";
    } catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

int main() {
    Fleet fleet;
    int choice;

    do {
        std::cout << "\n=== Robot Fleet Manager ===\n"
                  << "1. Add robot\n"
                  << "2. Remove robot\n"
                  << "3. Show all robots\n"
                  << "4. Work (single robot)\n"
                  << "5. Work all\n"
                  << "6. Charge all\n"
                  << "7. Assign task to robot\n"
                  << "8. Show task queue\n"
                  << "9. Start timed work on a robot\n"
                  << "0. Exit\n"
                  << "Choice: ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input.\n";
            choice = -1;
            continue;
        }

        switch (choice) {
            case 1: addRobot(fleet);        break;
            case 2: removeRobot(fleet);     break;
            case 3: std::cout << fleet;     break;
            case 4: workSingle(fleet);      break;
            case 5: fleet.work_all();       break;
            case 6: fleet.charge_all();     break;
            case 7: assignTask(fleet);      break;
            case 8: fleet.show_tasks();     break;
            case 9: startTimedWork(fleet);  break;
            case 0: std::cout << "Goodbye!\n"; break;
            default: std::cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}
