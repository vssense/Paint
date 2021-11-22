#include "rectangle.hpp"

bool IsInsideRectangle(const Rectangle& rect, Vec2<int> point)
{
    return rect.x0 <= point.x && point.x <= rect.x0 + rect.w &&
           rect.y0 <= point.y && point.y <= rect.y0 + rect.h;
}
