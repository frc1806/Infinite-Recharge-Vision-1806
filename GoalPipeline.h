#pragma once
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <vector>
#include <string>
#include <math.h>

namespace grip {

/**
* A representation of the different types of blurs that can be used.
*
*/
enum BlurType {
	BOX, GAUSSIAN, MEDIAN, BILATERAL
};
/**
* GoalPipeline class.
* 
* An OpenCV pipeline generated by GRIP.
*/
class GoalPipeline {
	private:
		cv::Mat blurOutput;
		cv::Mat hsvThresholdOutput;
		std::vector<std::vector<cv::Point> > findContoursOutput;
		std::vector<std::vector<cv::Point> > filterContoursOutput;
		void blur(cv::Mat &, BlurType &, double , cv::Mat &);
		void hsvThreshold(cv::Mat &, double [], double [], double [], cv::Mat &);
		void findContours(cv::Mat &, bool , std::vector<std::vector<cv::Point> > &);
		void filterContours(std::vector<std::vector<cv::Point> > &, double , double , double , double , double , double , double [], double , double , double , double , std::vector<std::vector<cv::Point> > &);
		void approximatePolygons(std::vector<std::vector<cv::Point>>& points, std::vector<std::vector<cv::Point>>& output, double minDistancePerSide);

	public:
		GoalPipeline();
		void Process(cv::Mat& source0);
		cv::Mat* GetBlurOutput();
		cv::Mat* GetHsvThresholdOutput();
		std::vector<std::vector<cv::Point> >* GetFindContoursOutput();
		std::vector<std::vector<cv::Point> >* GetFilterContoursOutput();
};


} // end namespace grip


