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
    return 19.63 / tan((M_PI / 180.0) * (mCameraInfo.getHorizontalAngle(topRight.x) - mCameraInfo.getHorizontalAngle(topLeft.x)) * (1/2));
}

double Target::getRobotToTargetAngle(){
    return mCameraInfo.getHorizontalAngle((topLeft.x + topRight.x) / 2);
}

double Target::getTargetSkewAngle(){
    return(atan((getLeftDistance() - getRightDistance() / 39.26)) * 180.0 / M_PI);
    
}

double Target::getLeftDistance(){
    return getDistanceToSide(topLeft.y, projectedBottomLeftY);
}

double Target::getRightDistance(){
    return getDistanceToSide(topRight.y, projectedBottomRightY);
}

double Target::getDistanceToSide(double topY, double bottomY){
    return 17.00 / tan((M_PI / 180.0) * (mCameraInfo.getVerticalAngle(topY) - mCameraInfo.getVerticalAngle(bottomY)));
} 

double Target::getRadAngleBetweenPoints(double px1, double py1, double px2, double py2, double cx1, double cy1)
{

 double dist1 = sqrt(  (px1-cx1)*(px1-cx1) + (py1-cy1)*(py1-cy1) );
 double dist2 = sqrt(  (px2-cx1)*(px2-cx1) + (py2-cy1)*(py2-cy1) );

 double Ax, Ay;
 double Bx, By;
 double Cx, Cy;

 //find closest point to C
 //printf("dist = %lf %lf\n", dist1, dist2);

 Cx = cx1;
 Cy = cy1;
 if(dist1 < dist2)
 {  
  Bx = px1;
  By = py1;  
  Ax = px2;
  Ay = py2;


 }else{
  Bx = px2;
  By = py2;
  Ax = px1;
  Ay = py1;
 }


 double Q1 = Cx - Ax;
 double Q2 = Cy - Ay;
 double P1 = Bx - Ax;
 double P2 = By - Ay;  


 double A = acos( (P1*Q1 + P2*Q2) / ( sqrt(P1*P1+P2*P2) * sqrt(Q1*Q1+Q2*Q2) ) );

 return A;
}

void Target::process(){
    if(mPoints.size() > 3)
    {
        try{
        auto comp = [](cv::Point a, cv::Point b) {return a.x > b.x;};
        std::sort(mPoints.begin(), mPoints.end(), comp);
        topLeft = mPoints[0];
        bottomLeft = mPoints[1];
        bottomRight = mPoints[2];
        topRight = mPoints[3];
        //http://www.softwareandfinance.com/Visual_CPP/VCPP_Intersection_Two_lines_EndPoints.html  was helpful in making this
        double bottomLineSlope = (bottomRight.y - bottomLeft.y) / (bottomRight.x - bottomRight.x);
        double bottomLineIntercept = (bottomLeft.y - bottomLineSlope) * bottomLeft.x;
        double leftLineSlope = tan(((M_PI)/2) +(getRadAngleBetweenPoints(bottomRight.x, bottomRight.y, topLeft.x, topLeft.y, bottomLeft.x, bottomLeft.y)-((2 * M_PI)/3)));
        double leftLineIntercept = (topLeft.y - leftLineSlope) * topLeft.x;
        double rightLineSlope = tan(((M_PI)/2) -(getRadAngleBetweenPoints(bottomLeft.x, bottomLeft.y, topRight.x, topRight.y, bottomRight.x, bottomRight.y) - ((2 * M_PI)/3)));
        double rightLineIntercept = (topRight.y - rightLineSlope) * topRight.x;
        projectedBottomLeftX = (leftLineIntercept - bottomLineIntercept) / (bottomLineSlope - leftLineSlope);
        projectedBottomLeftY = bottomLineSlope * projectedBottomLeftX + bottomLineIntercept;
        projectedBottomRightX = (rightLineIntercept - bottomLineIntercept) / (bottomLineSlope - rightLineSlope);
        projectedBottomRightY = bottomLineSlope * projectedBottomRightX + bottomLineIntercept;
        distance = getDistanceToTarget();
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
        topLeft = cv::Point(0, 0);
        bottomLeft = cv::Point(0, 0);
        bottomRight = cv::Point(0, 0);
        topRight = cv::Point(0, 0);
    }


}


