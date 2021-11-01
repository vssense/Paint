#ifndef _BRUSH_HPP_INCLUDED
#define _BRUSH_HPP_INCLUDED

#include "../graphics/color.hpp"

class Brush
{
public:
    Brush() : color_(kBlack) {}
    ~Brush() {}

    uint32_t GetColor() const { return color_; }
    void     SetColor(uint32_t color) { color_ = color; }
private:
    uint32_t color_;
};

#endif /* _BRUSH_HPP_INCLUDED */