#include "gui_system.hpp"

GUISystem::GUISystem(Window* window, GUIComponent* root) :
    window_(window), root_(root), listeners_(kEventsCount, nullptr)
{
    assert(window_);
    assert(root_);

    root_->SetGUISystem(this);
}

GUISystem::~GUISystem()
{
    delete root_;
}

void GUISystem::ProcessEvent(const Event& event)
{    
    if (listeners_[event.GetType()] != nullptr)
    {
        GUIComponent* listener = listeners_[event.GetType()];
        listeners_[event.GetType()] = nullptr;

        if (listener->ProcessMouseEvent(event))
        {
            return;
        }
    }

    switch (event.GetType())
    {
        case kMouseHover:
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

void GUISystem::Subscribe(GUIComponent* component, EventType type)
{
    listeners_[type] = component;
}

void GUISystem::Render()
{
    root_->Render();
}


