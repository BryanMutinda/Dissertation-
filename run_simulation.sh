#!/bin/bash
# run_simulation.sh

# Step 1 setup ROS envirnmnets
# Display setting up the environment
echo "Setting up ROS and package environment"

# Source ROS setup files
source ~/dissertation/Dissertation-/simulation_summit/devel/setup.bash
source ~/dissertation/Dissertation-/summit_sim_git/devel/setup.bash

# Step 2 ensure necessary libraries installed
# Display installing necessary packages to run program
pip3 install getKey

# Step 3 run launch file with simulation
# Launch the ROS launch file
roslaunch dissertation_sim simulation.launch

# Step 4 run keyboard control
#rosrun keyboard keyboard_node.py

