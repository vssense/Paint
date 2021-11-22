#ifndef _RECTANGLE_HPP_INCLUDED
#define _RECTANGLE_HPP_INCLUDED

#include <stdint.h>
#include "vector2.hpp"

struct Rectangle
{
    int x0;
    int y0;
    int w;
    int h;
};

bool IsInsideRectangle(const Rectangle& rect, Vec2<int> point);

#endif /* _RECTANGLE_HPP_INCLUDED */