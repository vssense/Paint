#ifndef _TOOL_HPP_INCLUDED
#define _TOOL_HPP_INCLUDED

#include "../graphics/color.hpp"
#include "../math/vector2.hpp"

class Texture;

class Tool
{
public:
    Tool() : color_(kBlack), thickness_(1) {}
    Tool(Color color) : color_(color), thickness_(1) {}
    Tool(Color color, uint32_t thickness) : color_(color), thickness_(thickness) {}

    virtual ~Tool() {}

    virtual void BeginDraw(Texture* texture, Vec2<int> coordinates) = 0;
    virtual void Draw     (Texture* texture, Vec2<int> coordinates, Vec2<int> displacement) = 0;
    virtual void EndDraw  (Texture* texture, Vec2<int> coordinates) = 0;

    void SetThickness(uint32_t thickness);

    void SetColor(Color color);

    uint32_t GetThickness() const;

    Color GetColor() const;

protected:
    Color color_;
    uint32_t thickness_;
};

#endif /* _TOOL_HPP_INCLUDED */
