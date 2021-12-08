#include "paint_gui_system.hpp"

class ComponentCloser : public IListener // FIXME: move it to GUISystem
{
public:
    virtual bool ProcessListenerEvent(const Event& event) override
    {
        assert(event.GetType() == kComponentClose);

        GUIComponent* component = event.GetValue().component;
        component->GetSystem()->Reset();
        component->GetParent()->Detach(component);
        delete component;

        return true;
    }
};

PaintGUISystem::~PaintGUISystem()
{
    delete listeners_[kComponentClose];
}

PaintGUISystem::PaintGUISystem(Window* window, GUIComponent* root) :
    GUISystem(window, root)
{
    listeners_[kComponentClose] = new ComponentCloser;
}

void PaintGUISystem::Reset()
{
    for (int i = 0; i < kEventsCount; ++i)
    {
        if (i != kComponentClose)
        {
            listeners_[i] = nullptr;
        }
    }
}
