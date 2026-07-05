# robotics-hw2-elias

A command-line C++ app that manages a fleet of robots. You can add robots, assign them tasks, make them work or charge, and run background timed work on mobile robots.

## File structure

```
robotics-hw2-elias/
├── include/
│   ├── robot.hpp           abstract base class
│   ├── mobile_robot.hpp    moves, supports background thread
│   ├── cleaning_robot.hpp  extends MobileRobot, cleans in a mode
│   ├── cooking_robot.hpp   extends Robot, cooks meals
│   ├── fleet.hpp           manages the robot collection + task queue
│   └── task.hpp            task struct with priority
├── src/
│   ├── robot.cpp
│   ├── mobile_robot.cpp
│   ├── cleaning_robot.cpp
│   ├── cooking_robot.cpp
│   ├── fleet.cpp
│   └── task.cpp
├── main.cpp
├── compile.sh
├── ANSWERS.md
└── ENV_CHECK.md
```

## How to compile and run

```bash
./compile.sh
./fleet_app
```

Or manually:

```bash
g++ -std=c++17 -Wall -Wextra src/*.cpp main.cpp -I include -pthread -o fleet_app
./fleet_app
```

## Problems and solutions

**Thread ordering bug** — in `start_work` I originally set `stop_ = false` before joining the previous thread, which meant a running thread would never get the stop signal. Fixed by doing `stop_ = true` → `join()` → `stop_ = false` in that order.

**priority_queue iteration** — `std::priority_queue` doesn't support iteration so I couldn't just loop over it to print tasks. Fixed by copying the queue into a local variable and popping from the copy.
