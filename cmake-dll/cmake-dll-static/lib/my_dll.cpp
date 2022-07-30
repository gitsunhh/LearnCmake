#include "my_dll.h"

int add(int a, int b) {
    return (a + b);
}

void DLLTEST::PrintHello()
{
	std::cout << "Hello world!" << std::endl;
}

namespace NS
{
	int COperation::i = 10;
	int COperation::Add(int a, int b)
	{
		return a + b;
	}
	int COperation::Sub(int a, int b)
	{
		return a-b;
	}
 
	int COperation::Avg(int* buf, int count)
	{
		int sum = 0;
		for (size_t i = 0; i < count; i++)
		{
			sum += buf[i];
		}
		return sum/count;
	}
}

void createAlphaMat()
{
    using namespace cv;
    cv::Mat mat(480, 640, CV_8UC4);
    for (int i = 0; i < mat.rows; i++) {
        for (int j = 0; j < mat.cols; j++) {
            Vec4b& rgba = mat.at<Vec4b>(i, j);
            rgba[0] = UCHAR_MAX;
            rgba[1] = saturate_cast<uchar> ((float(mat.cols - j)) / ((float)mat.cols) * UCHAR_MAX);
            rgba[2] = saturate_cast<uchar> ((float(mat.rows - i)) / ((float)mat.rows) * UCHAR_MAX); 
            rgba[3] = saturate_cast<uchar> (0.5 * (rgba[1] + rgba[2]));
        }
    }
    imwrite("alpha.jpg",mat);
}