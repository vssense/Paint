#ifndef _PAINT_PLUGIN_HPP_INCLUDED
#define _PAINT_PLUGIN_HPP_INCLUDED

#include <stdint.h>
#include <dlfcn.h>
#include "../math/vector2.hpp"

class Tool;

typedef Tool* (*GetToolPtr)();
typedef const char* (*GetNamePtr)();

const uint32_t kDefaultThickness = 5;

class IRenderTarget
{
public:
    virtual void SetPixel(uint32_t x, uint32_t y, uint32_t color) = 0;
    virtual void DrawRect(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t color) = 0;
    virtual void DrawLine(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t color) = 0;
    virtual void DrawLine(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t color,
                          uint32_t thickness) = 0;

    virtual ~IRenderTarget() {}

    virtual uint32_t GetXSize() const = 0;
    virtual uint32_t GetYSize() const = 0;
};

class Tool
{
public:
    Tool() : color_(0xFF'00'00'00), thickness_(5) {}
    Tool(uint32_t color) : color_(color), thickness_(1) {}
    Tool(uint32_t color, uint32_t thickness) : color_(color), thickness_(thickness) {}

    virtual ~Tool() {}

    virtual void BeginDraw(IRenderTarget* texture, Vec2<int> coordinates) = 0;
    virtual void Draw     (IRenderTarget* texture, Vec2<int> coordinates, Vec2<int> displacement) = 0;
    virtual void EndDraw  (IRenderTarget* texture, Vec2<int> coordinates) = 0;

    void SetThickness(uint32_t thickness)
    {
        thickness_ = thickness;
    }

    void SetColor(uint32_t color)
    {
        color_ = color;
    }

    uint32_t GetThickness() const
    {
        return thickness_;
    }

    uint32_t GetColor() const
    {
        return color_;
    }

protected:
    uint32_t color_;
    uint32_t thickness_;
};

#endif /* _PAINT_PLUGIN_HPP_INCLUDED */