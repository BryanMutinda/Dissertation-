#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include <ncurses.h>

// Global containers
bool keyInput = true;                           // Read keyboard inputs
double linear_vel = 0.0, angular_vel = 0.0;     // Initial velocities

void display() {
    clear();
    move(0, 0);
    printw("Key input: ");
    move(2, 0);
    printw("Linear velocity: %.2f \nAngular velocity: %.2f", linear_vel, angular_vel);
    refresh();
}

void keyboardInput() {
    int ch = getch();
    switch (ch) {
        case KEY_UP:
            linear_vel += 0.1;
            break;
        case KEY_DOWN:
            linear_vel -= 0.1;
            break;
        case KEY_LEFT:
            angular_vel += 0.1;
            break;
        case KEY_RIGHT:
            angular_vel -= 0.1;
            break;

        // Quit application    
        case 'q':
            keyInput = false;
            break;
        
        // Continue operation
        case 'c':
            keyInput = true;
            break;

        // Emergency stop
        case 'e':
            linear_vel = 0.0;
            angular_vel = 0.0;
            keyInput = false;
            break;
    }
}

int main(int argc, char **argv) {
    // Initialize the ROS node
    ros::init(argc, argv, "twist_publisher_node");
    ros::NodeHandle nh;

    // Create a publisher object
    ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("robot/move_base/cmd_vel", 10);

    // Initialize ncurses
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);

    // Set the rate of publishing
    ros::Rate rate(10);  // 10 Hz

    while (ros::ok() && keyInput) {
        // Twist message object
        geometry_msgs::Twist velocity;
        velocity.linear.x = linear_vel;
        velocity.angular.z = angular_vel;

        // Window display
        display();

        // Get key input and change variables
        keyboardInput();

        // Publish the Twist message
        pub.publish(velocity);

        // Sleep to maintain the desired rate
        rate.sleep();
    }

    // Cleanup ncurses
    endwin();

    return 0;
}
