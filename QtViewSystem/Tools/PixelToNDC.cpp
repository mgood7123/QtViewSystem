#include "PixelToNDC.h"

PixelToNDC::PixelToNDC(float width, float height) {
    resize(width, height);
}

void PixelToNDC::resize(float width, float height) {
    this->width = width;
    this->height = height;
}
