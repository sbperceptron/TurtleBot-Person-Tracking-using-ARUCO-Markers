#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <unistd.h>
#include <mutex>
#include "aruco.h"
#include "cvdrawingutils.h"
#include "opencv2/opencv.hpp"
#include <opencv2/aruco.hpp>
#include "ros/ros.h"
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/PointStamped.h>
#include <visualization_msgs/MarkerArray.h>
#include <visualization_msgs/Marker.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>

int main()
{
	const float markerLength = 2.0;
	printf("This program detects ArUco markers.\n");

	printf("Hit the ESC key to quit.\n");

	ros::Publisher pose_pub = n.advertise<geometry_msgs::Pose>("aruco/pose", 1);

	double K_[3][3] =

	{ { 675, 0, 320 },

	{ 0, 675, 240 },

	{ 0, 0, 1 } };

	cv::Mat K = cv::Mat(3, 3, CV_64F, K_).clone();



	double dist_[] = { 0, 0, 0, 0, 0 };

	cv::Mat distCoeffs = cv::Mat(5, 1, CV_64F, dist_).clone();



	cv::VideoCapture cap("C:/Users/SAICHAND/Documents/Visual Studio 2015/Projects/MyProject/video_1.avi");    



	if (!cap.isOpened()) {

		printf("error - can't open the camera or video; hit any key to quit\n");

		system("PAUSE");

		return EXIT_FAILURE;

	}

	double WIDTH = cap.get(CV_CAP_PROP_FRAME_WIDTH);

	double HEIGHT = cap.get(CV_CAP_PROP_FRAME_HEIGHT);

	printf("Image width=%f, height=%f\n", WIDTH, HEIGHT);

	cv::Mat image;

	cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_4X4_100);

	cv::Ptr<cv::aruco::DetectorParameters> detectorParams = cv::aruco::DetectorParameters::create();

	const cv::String fnameOut("output_video.avi");

	cv::VideoWriter outputVideo(fnameOut,

		cv::VideoWriter::fourcc('D', 'I', 'V', 'X'),

		30.0,

		cv::Size((int)WIDTH, (int)HEIGHT),

		true);

	while (1) {

		cap >> image;

		if (image.empty())    break;

		std::vector< int > markerIds;

		std::vector< std::vector<cv::Point2f> > markerCorners, rejectedCandidates;

		cv::aruco::detectMarkers(

			image,

			dictionary,  

			markerCorners,

			markerIds,    

			detectorParams,

			rejectedCandidates);



			for (unsigned int i = 0; i < markerIds.size(); i++) {

				if (markerIds[i] == 1) {

					cv::aruco::drawDetectedMarkers(image, markerCorners, markerIds);



					std::vector< cv::Vec3d > rvecs, tvecs;

					cv::aruco::estimatePoseSingleMarkers(

						markerCorners,

						markerLength,  

						K,             

						distCoeffs,    

						rvecs,          

						tvecs);        

							cv::Vec3d r = rvecs[i];

							cv::Vec3d t = tvecs[i];



					cv::aruco::drawAxis(image,

						K, distCoeffs,         

						r, t,                  

						0.5*markerLength);     				

				}

			}

		ros::init(argc, argv, "aruco_t");

  		ros::NodeHandle n;

		ros::Publisher pose_pub = n.advertise<geometry_msgs::Pose>("aruco/pose", 1);

		pose.position.x = x_t;

                pose.position.y = y_t;

                pose.position.z = z_t;

		pose_pub.publish(msg);

		cv::imshow("Image", image); 

		outputVideo << image;

		char key = cv::waitKey(1);

		if (key == 27)        break;        

	}

	return EXIT_SUCCESS;

}
