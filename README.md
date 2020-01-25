# Micromouse
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

We created a fully autonomous, maze-solving robot which we called the **micromouse**. The carcapable of scanning, mapping and traversing through various small mazes. The robot initially runs through the whole maze in order to map out the maze and find a more efficient path to traverse through the maze. To map out the maze, we installed a sensor on the left, front, and right of the robot to determine where there are routes available for the robot to travel. The robot then returns to the start of the maze and runs through it again using the most efficient path.

<p align="center">
  <img src="https://github.com/J-Douglas/Micromouse/blob/master/photos/Micromouse.png">
</p>

## Components

Listed below are the three types of components we considered while working on this project.

**Software**

- Terrain mapping: processes the location of the walls with sensors and creates a map of the maze
- Route generation: uses the map to find the most efficient path for the robot 
- Robot movement: allows the robot to traverse through the maze by rotating and turning the wheels

**Hardware**

- Arduino: microcontroller which processes all our software to calculate the most efficient path for the robot to take
- Motors and wheels: for traversing through the maze
- Chassis: the base frame of the vehicle that structurally supports the object
- Sensors: detects where the walls are during the mapping phase (HC SR04)
- Encoder: tells the mouse how far it has travelled, and its wheel position
- Battery: powers the robot

**Environment**

- Maze: walls made from cardboard for the robot to traverse through

## Robot Design

We designed and 3D printed a chassis that organized the circuitry to allow for easy reassembly. As well, one design tradeoff we made was to use two wheels and have the back of the robot trailing on the floor. Below is a schematic of the robot and diagram of the circuitry. 

<p align="center">
  <img src:"https://github.com/J-Douglas/Micromouse/blob/master/photos/MicromouseSchematic.png">
</p>

## Algorithm

For solving the maze, we decided to go with a *path simplifying algorithm*. We first decided that the robot will map the maze using the “left-hand rule”; the rule says that a robot is guaranteed to finish a maze as long as the robot sticks to the left wall. Throughout the mapping phase, the robot stores every decision it makes in an array. The robot then retraces its path to return to reach the start of the maze. Then, the path simplyfing algorithm looks at the array and removes combinations of decisions which are redundant. The robot finalizes the reformed array and transverse the maze using the more efficient path.
