#include "tool.hpp"

void Tool::SetThickness(uint32_t thickness)
{
    thickness_ = thickness;
}

void Tool::SetColor(Color color)
{
    color_ = color;
}

uint32_t Tool::GetThickness() const
{
    return thickness_;
}

Color Tool::GetColor() const
{
    return color_;
}
