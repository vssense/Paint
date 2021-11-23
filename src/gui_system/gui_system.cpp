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
        if (listeners_[event.GetType()]->ProcessListenerEvent(event))
        {
            return;
        }
    }

    ProcessMouseEvent(event);
}

void GUISystem::ProcessMouseEvent(const Event& event)
{
    root_->OnMouseEvent(event);
}

void GUISystem::Subscribe(GUIComponent* component, EventType type)
{
    assert(component);

    listeners_[type] = component;
}

void GUISystem::Reset()
{
    for (int i = 0; i < kEventsCount; ++i)
    {
        listeners_[i] = nullptr;
    }
}

void GUISystem::Unsubscribe(EventType type)
{
    listeners_[type] = nullptr;
}

void GUISystem::Render()
{
    root_->Render();
}
