#!/usr/bin/env python3

import rospy

from getkey import getkey, keys
from std_msgs.msg import String
from geometry_msgs.msg import Twist

rospy.init_node('keyboard_node')
pub = rospy.Publisher('/robot/cmd_vel', Twist, queue_size=10)
rate = rospy.Rate(20)  # 20 Hz
move = Twist()

rospy.loginfo("Keyboard Functional. Press Ctrl+C to exit.\n" 
        "Arrow keys used to move.\n" 
        "Press 'e' for emergency stop.\n"
        "Press 'e' again to continue")

# Initial values
move.linear.x = 0           # forward movement
move.angular.z = 0          # rotational movement

while not rospy.is_shutdown():
    key = getkey()

    if key == keys.UP:
        #rospy.loginfo("UP key pressed")
        move.linear.x = round(move.linear.x + 0.1, 2)
        
    elif key == keys.DOWN:
        move.linear.x = round(move.linear.x - 0.1, 2)
        
    elif key == keys.LEFT:
        # If robot is going backwards
        if move.linear.x < 0: 
            move.angular.z = round(move.angular.z - 0.1, 2)
        
        else: 
            move.angular.z = round(move.angular.z + 0.1, 2)

    elif key == keys.RIGHT:
        if move.linear.x < 0:
            move.angular.z = round(move.angular.z + 0.1, 2)

        else:
            move.angular.z = round(move.angular.z - 0.1, 2)

    else:
        rospy.loginfo("Use arrow keys")

    # Publish move
    print("Linear in x : ", move.linear.x)
    print("Angular in z: ", move.angular.z)
    print("\n\n")

    pub.publish(move)
    rate.sleep()

