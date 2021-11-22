#ifndef _BRUSH_HPP_INCLUDED
#define _BRUSH_HPP_INCLUDED

#include "tool.hpp"

const uint32_t kDefaultThickness = 5;

class Brush : public Tool
{
public:
    Brush() : Tool(kBlack, kDefaultThickness) {}
    virtual ~Brush() {}

    virtual void BeginDraw(Texture* texture, Vec2<int> coordinates) override;
    virtual void Draw     (Texture* texture, Vec2<int> start, Vec2<int> displacement) override;
    virtual void EndDraw  (Texture* texture, Vec2<int> coordinates) override;

};

#endif /* _BRUSH_HPP_INCLUDED */
