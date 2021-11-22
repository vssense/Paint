#include "rectangle.hpp"

bool IsInsideRectangle(const Rectangle& rect, Vec2<int> point)
{
    return rect.x0 <= point.x && point.x <= rect.x0 + rect.w &&
           rect.y0 <= point.y && point.y <= rect.y0 + rect.h;
}

Vec2<int> Rectangle::Start()
{
    return Vec2<int>(x0, y0);
}

Vec2<int> Rectangle::Size()
{
    return Vec2<int>(w, h);
}
