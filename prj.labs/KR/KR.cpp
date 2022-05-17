#include <opencv2/opencv.hpp>

int main() {
    cv::Mat I_0(450, 300, CV_32FC1);
    std::vector <std::vector<float>> color = { {255, 0, 127} , {0, 127, 255} };
    int xLine = 150; 
    int yLine = 70;
    cv::Rect2d mLine(0, 0, 150, 150);

    for (int j = 0; j < 3; j++) {
        mLine.y = j * xLine;
        for (int i = 0; i < 2; i++) {
            mLine.x = i * xLine;
            cv::Mat tmp = I_0(mLine);
            tmp = color[i][j] / 255;
            cv::circle(I_0, cv::Point(mLine.x + yLine, mLine.y + yLine), 55, color[1 - i][j] / 255, -1);
        }
    }

    cv::imshow("I_0", I_0);
    cv::imwrite("I_0.png", I_0*255);

    cv::Mat F1(2, 2, CV_32FC1);
    F1 = 0;
    F1.at<float>(0, 1) = 1;
    F1.at<float>(1, 0) = -1;
    cv::Mat I_1F;
    cv::filter2D(I_0, I_1F, -1, F1, cv::Point(0, 0));

    cv::Mat F2(2, 2, CV_32FC1);
    F2 = 0;
    F2.at<float>(1, 0) = 1;
    F2.at<float>(0, 1) = -1;
    cv::Mat I_2F;
    cv::filter2D(I_0, I_2F, -1, F2, cv::Point(0, 0));

    cv::Mat I_3(450, 300, CV_32FC1);
    for (int i = 0; i < I_3.rows; i++) {
        for (int j = 0; j < I_3.cols; j++) {
           std::sqrt(I_3.at<float>(i, j) = I_1F.at<float>(i, j) * I_1F.at<float>(i, j) + I_2F.at<float>(i, j) * I_2F.at<float>(i, j));
        }
    }

    I_1F = (I_1F + 1) / 2;
    cv::imshow("I_1F", I_1F);
    cv::imwrite("I_1F.png", I_1F * 255);

    I_2F = (I_2F + 1) / 2;
    cv::imshow("I_2F", I_2F);
    cv::imwrite("I_2F.png", I_2F * 255);

    cv::imshow("I_3", I_3);
    cv::imwrite("I_3.png", I_3 * 255);

    cv::waitKey(0);
}