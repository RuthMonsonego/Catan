#include "DrawingUtils.h"

void DrawingUtils::drawGrid(cv::Mat& img) {
    int rows = img.rows;
    int cols = img.cols;
    int stepX = cols / 5;
    int stepY = rows / 5;

    for (int i = 1; i < 5; ++i) {
        cv::line(img, cv::Point(i * stepX, 0), cv::Point(i * stepX, rows), cv::Scalar(0, 0, 0), 1);
        cv::line(img, cv::Point(0, i * stepY), cv::Point(cols, i * stepY), cv::Scalar(0, 0, 0), 1);
    }
    cv::rectangle(img, cv::Point(0, 0), cv::Point(cols - 1, rows - 1), cv::Scalar(0, 225, 0), 0.5);
}

bool DrawingUtils::checkCollision(int x1, int y1, int x2, int y2, int width, int height) {
    return (x1 < x2 + width && x1 + width > x2 && y1 < y2 + height && y1 + height > y2);
}

void DrawingUtils::overlayImage(cv::Mat& baseImg, const cv::Mat& overlayImg, int x, int y) {
    if (overlayImg.empty()) {
        std::cerr << "Error: overlay image is empty!" << std::endl;
        return;
    }

    cv::Rect roi(x, y, overlayImg.cols, overlayImg.rows);
    cv::Mat overlayImgROI = overlayImg(cv::Rect(0, 0, overlayImg.cols, overlayImg.rows));
    overlayImgROI.copyTo(baseImg(roi));
}
