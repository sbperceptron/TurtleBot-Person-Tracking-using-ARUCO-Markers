# TurtleBot: Person-Tracking-using-ARUCO-Markers
Aruco.cpp
1. Reading the camera stream and splitting the video stream into frames.
2. Using Computer Vision Techniques like corner detection and aruco marker detection from OpenCV to detect unique predefined Markers
3. Estimating the pose of the detected marker there by obtaining the position of the person wearing the Marker
4. Communicating the pose estimated as a publisher Node

follower.cpp
1. The follower program subscribes to the pose publisher Node 
2. The pose information is used to give velocity commands to the wheels of turtle-bot to adjust its position relative to the person it is tracking.
Tracking Persons Using ARUCO markers

[!["ARUCO MARKER POSE"](https://github.com/sbperceptron/Person-Tracking-using-ARUCO-Markers/blob/master/aruco_marker_pose.png)]
