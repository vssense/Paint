#include "paint_plugin.hpp"
#include "stdio.h"

class SquareTool : public Tool
{
public:
    SquareTool() {}

    virtual void BeginDraw(ITexture* texture, Vec2<int> coordinates);
    virtual void Draw     (ITexture* texture, Vec2<int> coordinates, Vec2<int> displacement);
    virtual void EndDraw  (ITexture* texture, Vec2<int> coordinates);
};

void SquareTool::BeginDraw(ITexture* texture, Vec2<int> coordinates)
{
    assert(texture);

    texture->DrawRect(coordinates.x, coordinates.y, 2 * thickness_, 2 * thickness_, color_);
}

void SquareTool::Draw(ITexture* texture, Vec2<int> coordinates, Vec2<int> displacement)
{
    assert(texture);

    texture->DrawRect(coordinates.x, coordinates.y, 2 * thickness_, 2 * thickness_, color_);
}

void SquareTool::EndDraw(ITexture* texture, Vec2<int> coordinates)
{
    assert(texture);

    texture->DrawRect(coordinates.x, coordinates.y, 2 * thickness_, 2 * thickness_, color_);
}


extern "C" const char* GetName()
{
    return "Plugin";
}

extern "C" Tool* GetTool()
{
    return new SquareTool();
}