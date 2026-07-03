# robotics-hw2-elias

## What it does

A command-line C++ application that manages a fleet of robots. Robots can be added, removed, assigned tasks, and commanded to work or charge. Supports background threaded work via `start_work`.

## How to compile and run

```bash
chmod +x compile.sh
./compile.sh
./fleet_app
```

Or manually:

```bash
g++ -std=c++17 -Wall -Wextra src/*.cpp main.cpp -I include -pthread -o fleet_app
./fleet_app
```

## Problems and solutions

<!-- Fill in as you work through the implementation -->
