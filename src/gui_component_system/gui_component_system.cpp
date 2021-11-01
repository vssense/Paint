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

void GUIComponentSystem::ProcessMouseEvent(Vec2<uint32_t> position, const Event& event)
{
    root_->OnMouseEvent(position, event);
}

void GUIComponentSystem::Render(Renderer* renderer)
{
    root_->Render(renderer, Vec2<uint32_t>(0, 0));
}


