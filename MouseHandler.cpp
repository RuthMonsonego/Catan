#include "MouseHandler.h"
#include <opencv2/opencv.hpp>

extern cv::Rect selection;
extern bool selecting;
extern bool selected;
extern cv::Mat screen;

void MouseHandler::onMouse(int event, int x, int y, void* param) {
    cv::Mat& image = screen;

    if (selecting) {
        cv::Mat tempImage = image.clone();
        cv::rectangle(tempImage, selection.tl(), cv::Point(x, y), cv::Scalar(255, 0, 0), 2);
        cv::imshow("Image", tempImage);
    }

    switch (event) {
    case cv::EVENT_LBUTTONDOWN:
        selecting = true;
        selected = false;
        selection = cv::Rect(x, y, 0, 0);
        break;
    case cv::EVENT_MOUSEMOVE:
        if (selecting) {
            selection.width = x - selection.x;
            selection.height = y - selection.y;
        }
        break;
    case cv::EVENT_LBUTTONUP:
        selecting = false;
        selected = true;
        selection.width = x - selection.x;
        selection.height = y - selection.y;
        cv::rectangle(image, selection, cv::Scalar(255, 0, 0), 2);
        cv::imshow("Image", image);
        std::cout << "Selected region: " << selection << std::endl;
        break;
    }
}
