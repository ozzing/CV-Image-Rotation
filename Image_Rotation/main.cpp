#include <iostream>
#include <opencv2\opencv.hpp>
#include <cmath>

# define PI 3.14159265358979323846


cv::Mat problem_a_rotate_forward(cv::Mat img, double angle){
	cv::Mat output;
	//////////////////////////////////////////////////////////////////////////////
	//                         START OF YOUR CODE                               //
	//////////////////////////////////////////////////////////////////////////////
	double radian = (double)(angle * PI / 180);
	double sinValue = (double)(sin(radian));
	double cosValue = (double)(cos(radian));
	double centerX = img.cols / 2.0;
	double centerY = img.rows / 2.0;
	double minX = img.cols, maxX = 0, minY = img.rows, maxY = 0;
	cv::Point2d center(centerX, centerY);
	cv::Mat temp(img.size(), img.type(), cv::Scalar(0));
	for (int x = 0; x < img.cols; ++x) {
		for (int y = 0; y < img.rows; ++y) {
			double xx(centerX + (x - centerX) * cosValue - (y - centerY) * sinValue);
			double yy(centerY + (x - centerX) * sinValue + (y - centerY) * cosValue);
			maxX = cv::max(maxX, xx);
			minX = cv::min(minX, xx);
			maxY = cv::max(maxY, yy);
			minY = cv::min(minY, yy);
		}
	}
	resize(temp, output, cv::Size(abs(maxX-minX), abs(maxY-minY)));
	for (int x = 0; x < img.cols; ++x) {
		for (int y = 0; y < img.rows; ++y) {
			double xx(centerX + (x - centerX) * cosValue - (y - centerY) * sinValue);
			double yy(centerY + (x - centerX) * sinValue + (y - centerY) * cosValue);

			yy += (maxY-minY) / 2.0 - centerY;
			xx += (maxX-minX) / 2.0 - centerX;

			if (xx < 0 || yy < 0 || xx >= output.cols || yy >= output.rows) continue;

			
			output.at < cv::Vec3b >(yy, xx)[0] = img.at<cv::Vec3b>(y, x)[0];
			output.at < cv::Vec3b >(yy, xx)[1] = img.at<cv::Vec3b>(y, x)[1];
			output.at < cv::Vec3b >(yy, xx)[2] = img.at<cv::Vec3b>(y, x)[2];
		}
	}

	//////////////////////////////////////////////////////////////////////////////
	//                          END OF YOUR CODE                                //
	//////////////////////////////////////////////////////////////////////////////
	cv::imshow("a_output", output); cv::waitKey(0);
	return output;
}

cv::Mat problem_b_rotate_backward(cv::Mat img, double angle){
	cv::Mat output;

	//////////////////////////////////////////////////////////////////////////////
	//                         START OF YOUR CODE                               //
	//////////////////////////////////////////////////////////////////////////////
	double radian = (double)(angle * PI / 180);
	double sinValue = (double)(sin(radian));
	double cosValue = (double)(cos(radian));
	double centerX = img.cols / 2.0;
	double centerY = img.rows / 2.0;
	double minX = img.cols, maxX = 0, minY = img.rows, maxY = 0;
	cv::Point2d center(centerX, centerY);
	for (int x = 0; x < img.cols; ++x) {
		for (int y = 0; y < img.rows; ++y) {
			double xx(centerX + (x - centerX) * cosValue - (y - centerY) * sinValue);
			double yy(centerY + (x - centerX) * sinValue + (y - centerY) * cosValue);
			maxX = cv::max(maxX, xx);
			minX = cv::min(minX, xx);
			maxY = cv::max(maxY, yy);
			minY = cv::min(minY, yy);
		}
	}
	cv::Mat temp(cv::Size(maxX - minX, maxY - minY), img.type(), cv::Scalar(0));
	resize(temp, output, cv::Size(maxX - minX, maxY - minY));
	centerX = temp.cols / 2.0; centerY = temp.rows / 2.0;

	for (int xx = 0; xx < temp.cols; ++xx) {
		for (int yy = 0; yy < temp.rows; ++yy) {
			double x = (centerX + (xx - centerX) * cosValue + (yy - centerY) * sinValue);
			double y = (centerY - (xx - centerX) * sinValue + (yy - centerY) * cosValue);

			y -= (maxY - minY) / 2.0 - img.rows / 2.0;
			x -= (maxX - minX) / 2.0 - img.cols / 2.0;

			if (x < 0 || y < 0 || x >= img.cols || y >= img.rows) continue;
			if (xx < 0 || yy < 0 || xx >= output.cols || yy >= output.rows) continue;

			output.at < cv::Vec3b >(yy, xx)[0] = img.at<cv::Vec3b>(y, x)[0];
			output.at < cv::Vec3b >(yy, xx)[1] = img.at<cv::Vec3b>(y, x)[1];
			output.at < cv::Vec3b >(yy, xx)[2] = img.at<cv::Vec3b>(y, x)[2];
		}
	}

	//////////////////////////////////////////////////////////////////////////////
	//                          END OF YOUR CODE                                //
	//////////////////////////////////////////////////////////////////////////////

	cv::imshow("b_output", output); cv::waitKey(0);

	return output;
}

cv::Mat problem_c_rotate_backward_interarea(cv::Mat img, double angle){
	cv::Mat output;

	//////////////////////////////////////////////////////////////////////////////
	//                         START OF YOUR CODE                               //
	//////////////////////////////////////////////////////////////////////////////
	double radian = (double)(angle * PI / 180);
	double sinValue = (double)(sin(radian));
	double cosValue = (double)(cos(radian));
	double centerX = img.cols / 2.0;
	double centerY = img.rows / 2.0;
	double minX = img.cols, maxX = 0, minY = img.rows, maxY = 0;
	cv::Point2d center(centerX, centerY);
	for (int x = 0; x < img.cols; ++x) {
		for (int y = 0; y < img.rows; ++y) {
			double xx(centerX + (x - centerX) * cosValue - (y - centerY) * sinValue);
			double yy(centerY + (x - centerX) * sinValue + (y - centerY) * cosValue);
			maxX = cv::max(maxX, xx);
			minX = cv::min(minX, xx);
			maxY = cv::max(maxY, yy);
			minY = cv::min(minY, yy);
		}
	}
	cv::Mat temp(cv::Size(maxX - minX, maxY - minY), img.type(), cv::Scalar(0));
	resize(temp, output, cv::Size(maxX - minX, maxY - minY));
	centerX = temp.cols / 2.0; centerY = temp.rows / 2.0;

	for (int xx = 0; xx < temp.cols; ++xx) {
		for (int yy = 0; yy < temp.rows; ++yy) {
			double x = (centerX + (xx - centerX) * cosValue + (yy - centerY) * sinValue);
			double y = (centerY - (xx - centerX) * sinValue + (yy - centerY) * cosValue);

			y -= (maxY - minY) / 2.0 - img.rows / 2.0;
			x -= (maxX - minX) / 2.0 - img.cols / 2.0;

			double ceilX(ceil(x));
			double floorX(floor(x));
			double ceilY(ceil(y));
			double floorY(floor(y));
			double deltaX(x - floorX);
			double deltaY(y - floorY);

			if (ceilX < 0 || ceilY < 0 || floorX < 0 || floorY < 0 || ceilX >= img.cols || ceilY >= img.rows || floorX >= img.cols || floorY >= img.rows) continue;

			cv::Vec3b lTop(img.at < cv::Vec3b >((int)floorY, (int)floorX));
			cv::Vec3b rTop(img.at < cv::Vec3b >((int)floorY, (int)ceilX));
			cv::Vec3b lBot(img.at < cv::Vec3b >((int)ceilY, (int)floorX));
			cv::Vec3b rBot(img.at < cv::Vec3b >((int)ceilY, (int)ceilX));

			int red((int)ceil(((1 - deltaY) * ((1 - deltaX) * lTop[0] + deltaX * rTop[0])) + (deltaY * ((1 - deltaX) * lBot[0] + deltaX * rBot[0]))));
			int green((int)ceil(((1 - deltaY) * ((1 - deltaX) * lTop[1] + deltaX * rTop[1])) + (deltaY * ((1 - deltaX) * lBot[1] + deltaX * rBot[1]))));
			int blue((int)ceil(((1 - deltaY) * ((1 - deltaX) * lTop[2] + deltaX * rTop[2])) + (deltaY * ((1 - deltaX) * lBot[2] + deltaX * rBot[2]))));

			output.at < cv::Vec3b >(yy, xx)[0] = (float)red > 255 ? 255 : red < 0 ? 0 :  red;
			output.at < cv::Vec3b >(yy, xx)[1] = (float)green > 255 ? 255 : green < 0 ? 0 : green;
			output.at < cv::Vec3b >(yy, xx)[2] = (float)blue > 255 ? 255 : blue < 0 ? 0 : blue;
		}
	}
	//////////////////////////////////////////////////////////////////////////////
	//                          END OF YOUR CODE                                //
	//////////////////////////////////////////////////////////////////////////////

	cv::imshow("c_output", output); cv::waitKey(0);

	return output;
}

cv::Mat Example_change_brightness(cv::Mat img, int num, int x, int y) {
	/*
	img : input image
	num : number for brightness (increase or decrease)
	x : x coordinate of image (for square part)
	y : y coordinate of image (for square part)

	*/
	cv::Mat output = img.clone();
	int size = 100;
	int height = (y + 100 > img.cols) ? img.cols : y + 100;
	int width = (x + 100 > img.rows) ? img.rows : x + 100;

	for (int i = x; i < width; i++)
	{
		for (int j = y; j < height; j++)
		{
			for (int c = 0; c < img.channels(); c++)
			{
				int t = img.at<cv::Vec3b>(i, j)[c] + num;
				output.at<cv::Vec3b>(i, j)[c] = t > 255 ? 255 : t < 0 ? 0 : t;
			}
		}

	}
	cv::imshow("output1", img);
	cv::imshow("output2", output);
	cv::waitKey(0);
	return output;
}

int main(void){

	double angle = 25.0f; 

	cv::Mat input = cv::imread("lena.jpg");
	
	//Fill problem_a_rotate_forward and show output
	problem_a_rotate_forward(input, angle);
	//Fill problem_b_rotate_backward and show output
	problem_b_rotate_backward(input, angle);
	//Fill problem_c_rotate_backward_interarea and show output
	problem_c_rotate_backward_interarea(input, angle);
	//Example how to access pixel value, change params if you want
	Example_change_brightness(input, 100, 50, 125);

}