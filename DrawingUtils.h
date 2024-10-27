#ifndef DRAWING_UTILS_H
#define DRAWING_UTILS_H

#include <opencv2/opencv.hpp>

class DrawingUtils {
public:
    static void drawGrid(cv::Mat& img);
    static bool checkCollision(int x1, int y1, int x2, int y2, int width, int height);
    static void overlayImage(cv::Mat& baseImg, const cv::Mat& overlayImg, int x, int y);
};

#endif // DRAWING_UTILS_H
