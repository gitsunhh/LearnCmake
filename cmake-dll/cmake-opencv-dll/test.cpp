#include <iostream>
#include <opencv2/opencv.hpp>
#include "show_img.h" //cmake ： include_directories("./show_img") ，因此不需要"show_img/show_img.h"
int main()
{
	std::string str = R"(Hello World!)";
	print_string(str);
	std::string path = R"(color.jpeg)";
	cv::Mat img = show_img(path);
	cv::imshow("Src", img);
	cv::waitKey(0);	
	cv::destroyAllWindows();
 
	return 1;
}