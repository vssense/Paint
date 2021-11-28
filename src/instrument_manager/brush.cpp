#include "brush.hpp"

void Brush::ActionBegin(ITexture* canvas, int x, int y)
{
    assert(canvas);
    
    canvas->DrawCircle(x, y, 10, 0xFF'00'00'00);
}

void Brush::Action(ITexture* canvas, int x, int y, int dx, int dy)
{
    assert(canvas);

    canvas->DrawThickLine(x, y, x + dx, y + dy, 10, 0xFF'00'00'00);
}

void Brush::ActionEnd(ITexture* canvas, int x, int y)
{
    assert(canvas);

    canvas->DrawCircle(x, y, 10, 0xFF'00'00'00);
}

const char* Brush::GetIconFileName() const
{
    return "Brush";
}

IPreferencesPanel* Brush::GetPreferencesPanel() const
{
    return nullptr;
}
