#pragma once
#include "CameraInfo.h"
#include <opencv2/core/core.hpp>
#include <vector>

class Target
{
    
    public:
        Target(const std::vector<cv::Point>& points, CameraInfo cameraInfo);
        bool isValid();
        void process();
        double getDistanceToTarget();
        double getRobotToTargetAngle();
        double getTargetSkewAngle();
    
    private:
        double getLeftDistance();
        double getRightDistance();
        double getDistanceToSide(double topY, double bottomY);
	double getRadAngleBetweenPoints(double px1, double py1, double px2, double py2, double cx1, double cy1);

        std::vector<cv::Point> mPoints;
        CameraInfo mCameraInfo;
        cv::Point topLeft;
        cv::Point bottomLeft;
        cv::Point topRight;
        cv::Point bottomRight;
	bool valid;
        double projectedBottomLeftX;
        double projectedBottomLeftY;
        double projectedBottomRightX;
        double projectedBottomRightY;
        double distance;

};
