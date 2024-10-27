#ifndef MOUSE_HANDLER_H
#define MOUSE_HANDLER_H

#include <opencv2/opencv.hpp>

class MouseHandler {
public:
    static void onMouse(int event, int x, int y, void* param);
};

#endif // MOUSE_HANDLER_H
