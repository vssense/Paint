#include "gui_system.hpp"

class CanvasCloser : public IListener
{
public:
    virtual bool ProcessListenerEvent(const Event& event) override
    {
        assert(event.GetType() == kCanvasClose);

        GUIComponent* canvas = event.GetValue().canvas;
        canvas->GetSystem()->UnSubscribe(canvas);
        canvas->GetParent()->Detach(canvas);
        delete canvas;
        return true;
    }
};

GUISystem::GUISystem(Window* window, GUIComponent* root) :
    window_(window), root_(root), listeners_(kEventsCount, nullptr)
{
    assert(window_);
    assert(root_);

    root_->SetGUISystem(this);
    listeners_[kCanvasClose] = new CanvasCloser;
}

GUISystem::~GUISystem()
{
    delete root_;
    delete listeners_[kCanvasClose];
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
    assert(component);

    listeners_[type] = component;
}

void GUISystem::UnSubscribe(GUIComponent* component)
{
    for (size_t i = 0; i < listeners_.size(); ++i)
    {
        if (listeners_[i] == component)
        {
            listeners_[i] = nullptr;
        }
    }
}

void GUISystem::UnSubscribe(EventType type)
{
    listeners_[type] = nullptr;
}

void GUISystem::Render()
{
    root_->Render();
}
