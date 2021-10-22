#ifndef _RECTANGLE_HPP_INCLUDED
#define _RECTANGLE_HPP_INCLUDED

#include "vector2.hpp"

struct Rectangle
{
    float x0;
    float y0;
    float w;
    float h;
};

bool IsInsideRectangle(const Rectangle& rect, Vec2<float> point);

#endif /* _RECTANGLE_HPP_INCLUDED */