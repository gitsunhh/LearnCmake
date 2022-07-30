#ifndef SHOW_IMG_H_
#define SHOW_IMG_H_
 
#include <iostream>
#include <opencv2/opencv.hpp>

#define EXPORT_DLL __declspec(dllexport)
EXPORT_DLL cv::Mat show_img(const std::string &path);
EXPORT_DLL bool print_string(const std::string &str);

#endif