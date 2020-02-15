#pragma once
#include <math.h>

class CameraInfo{
    public:
        inline CameraInfo(double horizontalFOV, double horizontalResolution, double verticalFOV, double verticalResolution){mHorizontalResolution = horizontalResolution; mHorizontalFOV = horizontalFOV; mVerticalFOV = verticalFOV; mVerticalResolution = verticalResolution;}
        inline double getHorizontalFOV(){ return mHorizontalFOV;}
        inline double getHorizontalResolution(){return mHorizontalResolution;}
        inline double getHorizontalFocalLength() {return mHorizontalResolution / (2* tan(((mHorizontalFOV * M_PI) / 180.0)/2));}
        inline double getHorizontalAngle(double pixel){return (atan((pixel - (getHorizontalResolution()/2))/getHorizontalFocalLength())* 180.0) / M_PI;}
        inline double getVerticalFOV(){return mVerticalFOV;}
        inline double getVerticalResolution(){return mVerticalResolution;}
        inline double getVerticalFocalLength() {return mVerticalResolution / (2* tan(((mVerticalFOV * M_PI) / 180.0)/2));}
        inline double getVerticalAngle(double pixel){return (atan((pixel - (getVerticalResolution()/2))/getVerticalFocalLength())* 180.0) / M_PI;}
    private:
        double mHorizontalFOV;
        double mHorizontalResolution;
        double mVerticalFOV;
        double mVerticalResolution;
}