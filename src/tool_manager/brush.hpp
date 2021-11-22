#ifndef _BRUSH_HPP_INCLUDED
#define _BRUSH_HPP_INCLUDED

// #include "tool.hpp"
// #include "tool_texture.hpp"
#include "../plugins/paint_plugin.hpp"

class Brush : public Tool
{
public:
    Brush() {}
    virtual ~Brush() {}

    virtual void BeginDraw(IRenderTarget* texture, Vec2<int> coordinates) override;
    virtual void Draw     (IRenderTarget* texture, Vec2<int> start, Vec2<int> displacement) override;
    virtual void EndDraw  (IRenderTarget* texture, Vec2<int> coordinates) override;

};

#endif /* _BRUSH_HPP_INCLUDED */
