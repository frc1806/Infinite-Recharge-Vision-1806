#include "Target.h"
#include <algorithm>
#include "CameraInfo.h"

Target::Target(const std::vector<cv::Point>& points, CameraInfo cameraInfo){
    mPoints = points;
    mCameraInfo = cameraInfo;
}

bool Target::isValid(){
    return valid;
    
}

double Target::getDistanceToTarget(){
    return 19.63 / tan((M_PI / 180.0) * (mCameraInfo.getHorizontalAngle(right.x) - mCameraInfo.getHorizontalAngle(left.x)) * (1/2));
}

double Target::getRobotToTargetAngle(){
    return mCameraInfo.getHorizontalAngle((left.x + right.x) / 2);
}

double Target::getTargetSkewAngle(){
    return(atan((getLeftDistance() - getRightDistance() / 39.26)) * 180.0 / M_PI);
    
}

double Target::getLeftDistance(){
    return getDistanceToSide(left.y);
}

double Target::getRightDistance(){
    return getDistanceToSide(right.y);
}

double Target::getDistanceToSide(double y){
    return (100.0 - mCameraInfo.getCameraHeight()) / tan((M_PI / 180.0) * mCameraInfo.getVerticalAngle(y)); //some trig; TODO: Find actual distance from camera to goal
} 


void Target::process(){
    if(mPoints.size() > 3)
    {
        try{
        auto comp = [](cv::Point a, cv::Point b) {return a.x > b.x;};
        std::sort(mPoints.begin(), mPoints.end(), comp);
        left = mPoints.front;
        right = mPoints.back;

        double distance = getDistanceToTarget();
        if(distance < 10 || distance > 636 || abs(getTargetSkewAngle()) > 50)
        {
            valid = false;
        }
	}
        catch(...){
            valid = false;
        }
    }
    else{
        left = cv::Point(0, 0);
        right = cv::Point(0, 0);
    }


}


