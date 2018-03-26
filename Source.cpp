#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include "opencv2/imgcodecs.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <sstream>

using namespace std;
using namespace cv;



int main()
{
	cv::Mat input1 = cv::imread("result_akaze.jpg");
	cv::Mat input2 = cv::imread("result_orb.jpg");

	cv::resize(input1, input1, input2.size());

	cv::Mat diff;
	cv::absdiff(input1, input2, diff);

	cv::Mat diff1Channel;
	// WARNING: this will weight channels differently! - instead you might want some different metric here. e.g. (R+B+G)/3 or MAX(R,G,B)
	cv::cvtColor(diff, diff1Channel, CV_BGR2GRAY);

	float threshold = 30; // pixel may differ only up to "threshold" to count as being "similar"

	cv::Mat mask = diff1Channel < threshold;

	cv::imshow("similar in both images", mask);

	// use similar regions in new image: Use black as background
	cv::Mat similarRegions(input1.size(), input1.type(), cv::Scalar::all(0));

	// copy masked area
	input1.copyTo(similarRegions, mask);


	cv::imshow("input1", input1);
	cv::imshow("input2", input2);
	cv::imshow("similar regions", similarRegions);
	cv::imwrite("../outputData/Similar_result.png", similarRegions);
	cout << "absolute difference = " << endl << " " << sum(diff) << endl << endl;
	cv::waitKey(0);
	return 0;
}