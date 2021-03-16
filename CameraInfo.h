#pragma once
#include <math.h>
#inlcude "Util.h"

class CameraInfo{
    public:
        inline CameraInfo(){mHorizontalResolution = 0; mHorizontalFOV = 0; mVerticalFOV = 0; mVerticalResolution = 0;}
        inline CameraInfo(double horizontalFOV, double horizontalResolution, double verticalFOV, double verticalResolution){mHorizontalResolution = horizontalResolution; mHorizontalFOV = horizontalFOV; mVerticalFOV = verticalFOV; mVerticalResolution = verticalResolution;
                                mVerticalTilt = 0.0; mCameraHeight = 0.0;}
        inline void setCameraPositionInfo(double verticalTilt, double cameraHeight){mVerticalTilt = verticalTilt; mCameraHeight = cameraHeight;}
        inline double getHorizontalFOV(){ return mHorizontalFOV;}
        inline double getHorizontalResolution(){return mHorizontalResolution;}
        inline double getHorizontalFocalLength() {return mHorizontalResolution / (2* tan(((Util::degreesToRadians(mHorizontalFOV))/2));}
        inline double getHorizontalAngle(double pixel){return Util::radiansToDegrees(atan((pixel - (getHorizontalResolution()/2))/getHorizontalFocalLength()));}
        inline double getVerticalFOV(){return mVerticalFOV;}
        inline double getVerticalResolution(){return mVerticalResolution;}
        inline double getVerticalFocalLength() {return mVerticalResolution / (2* tan(((Util::degreesToRadians(mVerticalFOV))/2));}
        inline double getVerticalAngle(double pixel){return mVerticalTilt + Util::radiansToDegrees(atan((pixel - (getVerticalResolution()/2))/getVerticalFocalLength()));}
        inline double getCameraHeight(){return mCameraHeight;}

    private:
        double mHorizontalFOV;
        double mHorizontalResolution;
        double mVerticalFOV;
        double mVerticalResolution;
        double mVerticalTilt;
        double mCameraHeight;
}