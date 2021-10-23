#ifndef _RECTANGLE_HPP_INCLUDED
#define _RECTANGLE_HPP_INCLUDED

#include <stdint.h>
#include "vector2.hpp"

struct Rectangle
{
    uint32_t x0;
    uint32_t y0;
    uint32_t w;
    uint32_t h;
};

bool IsInsideRectangle(const Rectangle& rect, Vec2<float> point);

#endif /* _RECTANGLE_HPP_INCLUDED */