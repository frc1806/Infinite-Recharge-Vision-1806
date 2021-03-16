#pragma once

namespace Util
{
    double degreesToRadians(double degrees)
    {
        return degrees * (M_PI / 180.0);
    }

    double radiansToDegrees(double radians)
    {
        return radians / (M_PI / 180.0);
    }
}