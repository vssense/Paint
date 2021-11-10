#include "gui_system.hpp"

GUISystem::GUISystem(Window* window, GUIComponent* root) :
    window_(window), root_(root) {}

GUISystem::~GUISystem()
{
    delete root_;
}

void GUISystem::ProcessEvent(const Event& event)
{
    switch (event.GetType())
    {
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

void GUISystem::ProcessMouseEvent(Vec2<uint32_t> position, const Event& event)
{
    root_->OnMouseEvent(position, event);
}

void GUISystem::Render()
{
    root_->Render();
}


