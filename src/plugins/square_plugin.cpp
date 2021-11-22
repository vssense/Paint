#include "paint_plugin.hpp"
#include "stdio.h"

class SquareTool : public Tool
{
public:
    SquareTool() {}

    virtual void BeginDraw(IRenderTarget* texture, Vec2<int> coordinates);
    virtual void Draw     (IRenderTarget* texture, Vec2<int> coordinates, Vec2<int> displacement);
    virtual void EndDraw  (IRenderTarget* texture, Vec2<int> coordinates);
};

void SquareTool::BeginDraw(IRenderTarget* texture, Vec2<int> coordinates)
{
    assert(texture);

    texture->DrawRect(coordinates.x, coordinates.y, 2 * thickness_, 2 * thickness_, color_);
}

void SquareTool::Draw(IRenderTarget* texture, Vec2<int> coordinates, Vec2<int> displacement)
{
    assert(texture);

    texture->DrawRect(coordinates.x, coordinates.y, 2 * thickness_, 2 * thickness_, color_);
}

void SquareTool::EndDraw(IRenderTarget* texture, Vec2<int> coordinates)
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