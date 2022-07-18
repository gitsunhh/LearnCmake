#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;


void createAlphaMat(Mat& mat)
{
    for (int i = 0; i < mat.rows; i++) {
        for (int j = 0; j < mat.cols; j++) {
            Vec4b& rgba = mat.at<Vec4b>(i, j);
            rgba[0] = UCHAR_MAX;
            rgba[1] = saturate_cast<uchar> ((float(mat.cols - j)) / ((float)mat.cols) * UCHAR_MAX);
            rgba[2] = saturate_cast<uchar> ((float(mat.rows - i)) / ((float)mat.rows) * UCHAR_MAX); 
            rgba[3] = saturate_cast<uchar> (0.5 * (rgba[1] + rgba[2]));
        }
    }
}


int main()
{
    Mat mat(480, 640, CV_8UC4);
    createAlphaMat(mat);
    cv::imshow("alpha", mat);
    waitKey(0);

    return 0;
}