#include "Target.h"
#include <algorithm>
#include "CameraInfo.h"
#include "Util.h"

//This may all seem confusing, but it's written for a camera that is in portrait mode, rotated left 90 degrees.

Target::Target(const std::vector<cv::Point>& points, CameraInfo cameraInfo){
    mPoints = points;
    mCameraInfo = cameraInfo;
}

bool Target::isValid(){
    return valid;
    
}

double Target::getDistanceToTarget(){
    return (getLeftDistance() + getRightDistance()) / 2;
}

double Target::getRobotToTargetAngle(){
    return mCameraInfo.getVerticalAngle((left.y + right.y) / 2);
}

double Target::getTargetSkewAngle(){
    return(Util::radiansToDegrees(atan(getLeftDistance() - getRightDistance() / 39.26)));
    
}

double Target::getLeftDistance(){
    return getDistanceToSide(left.x);
}

double Target::getRightDistance(){
    return getDistanceToSide(right.x);
}

double Target::getDistanceToSide(double x){
    return (98.25 - mCameraInfo.getCameraHeight()) / tan(Util::degreesToRadians(mCameraInfo.getHorizontalAngle(x))); //some trig; TODO: Find actual distance from camera to goal
} 


void Target::process(){
    if(mPoints.size() > 3)
    {
        valid = true;
        left = false;
        right = false;
        try{
        auto comp = [](cv::Point a, cv::Point b) {return a.y > b.y;};
        std::sort(mPoints.begin(), mPoints.end(), comp);
        left = mPoints.front;
        right = mPoints.back;

        double distance = getDistanceToTarget();
        if(distance < 10 || distance > 636 || abs(getTargetSkewAngle()) > 50)
        {
            valid = false;
        }

        if(mCameraInfo.getVerticalAngle(right.y) > mCameraInfo.getVerticalFOV * .49)
        {
            right = true;
        }
        if(mCameraInfo.getVerticalAngle(right.y) < - mCameraInfo.getVerticalFOV * .49)
        {
            left = true;
        }

	}
        catch(...){
            valid = false;
        }
    }
    else{
        left = cv::Point(0, 0);
        right = cv::Point(0, 0);
        valid = false;
    }


}


