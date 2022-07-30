#include "show_img.h"

cv::Mat show_img(const std::string &path)
{
	cv::Mat img = cv::imread(path, cv::IMREAD_UNCHANGED);
	return img;
}
bool print_string(const std::string &str)
{
	std::cout << str << std::endl;
	return true;
}