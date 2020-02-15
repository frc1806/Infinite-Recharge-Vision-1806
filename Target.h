#pragma once
#include <CameraInfo.h>
#include <opencv2/core/core.hpp>
#include <vector>
#include <CameraInfo.h>

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
        double getDistanceToSide(double pixelHeight);

        std::vector<cv::Point> mPoints;
        CameraInfo mCameraInfo;
        cv::Point topLeft;
        cv::Point bottomLeft;
        cv::Point topRight;
        cv::Point bottomRight;

}