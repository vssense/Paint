#ifndef _BRUSH_HPP_INCLUDED
#define _BRUSH_HPP_INCLUDED

#include "../graphics/color.hpp"

class Brush
{
public:
    Brush() : color_(kBlack), thickness_(5) {}
    ~Brush() {}

    uint32_t GetColor() const { return color_; }
    void     SetColor(uint32_t color) { color_ = color; }

    uint32_t& GetThickness() { return thickness_; }
    void      SetThickness(uint32_t thickness) { thickness_ = thickness; }

private:
    uint32_t color_;
    uint32_t thickness_;
};

#endif /* _BRUSH_HPP_INCLUDED */