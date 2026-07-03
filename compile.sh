#!/bin/bash
g++ -std=c++17 -Wall -Wextra \
    src/robot.cpp src/task.cpp src/mobile_robot.cpp src/fleet.cpp \
    main.cpp \
    -I include \
    -pthread \
    -o fleet_app
