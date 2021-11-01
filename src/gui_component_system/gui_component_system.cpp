#include "gui_component_system.hpp"

GUIComponentSystem::GUIComponentSystem(Window* window, GUIComponent* root) :
    window_(window), root_(root) {}

GUIComponentSystem::~GUIComponentSystem()
{
    delete root_;
}

void GUIComponentSystem::ProcessEvent(const Event& event)
{
    switch (event.GetType())
    {
        case kMouseButtonOldRelease:
        case kMouseButtonRelease:
        case kMouseButtonPress:
        {
            ProcessMouseEvent(event.GetValue().coordinates, event);
            break;
        }
        case kMouseMotion:
        {
            ProcessMouseEvent(event.GetValue().motion.start, event);
            break;
        }
        default:
        {
            break;
        }
    }
}
Brush& GUIComponentSystem::GetBrush()
{
    return brush_;
}
void GUIComponentSystem::SetBrush(const Brush& brush)
{
    brush_ = brush;
}

void GUIComponentSystem::ProcessMouseEvent(Vec2<uint32_t> position, const Event& event)
{
    root_->OnMouseEvent(position, event, Vec2<uint32_t>(0, 0));
}

void GUIComponentSystem::Render(Renderer* renderer)
{
    root_->Render(renderer, Vec2<uint32_t>(0, 0));
}


