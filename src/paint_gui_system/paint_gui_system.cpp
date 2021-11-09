#include "paint_gui_system.hpp"

PaintGUISystem::PaintGUISystem(Window* window, GUIComponent* root) :
    GUISystem(window, root) {}

PaintGUISystem::~PaintGUISystem() {}

Brush& PaintGUISystem::GetBrush()
{
    return brush_;
}

void PaintGUISystem::SetBrush(const Brush& brush)
{
    brush_ = brush;
}
