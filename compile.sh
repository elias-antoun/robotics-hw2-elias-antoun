#!/bin/bash
# Always run from the directory this script lives in
DIR="$(cd "$(dirname "$0")" && pwd)"
cd "$DIR"

g++ -std=c++17 -Wall -Wextra \
    src/robot.cpp src/task.cpp src/mobile_robot.cpp \
    src/cleaning_robot.cpp src/cooking_robot.cpp src/fleet.cpp \
    main.cpp \
    -I include \
    -pthread \
    -o fleet_app
