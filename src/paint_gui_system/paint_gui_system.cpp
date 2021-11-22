#include "paint_gui_system.hpp"

class CanvasCloser : public IListener
{
public:
    virtual bool ProcessListenerEvent(const Event& event) override
    {
        assert(event.GetType() == kCanvasClose);

        GUIComponent* canvas = event.GetValue().canvas;
        canvas->GetSystem()->Reset();
        canvas->GetParent()->Detach(canvas);
        delete canvas;
        return true;
    }
};

PaintGUISystem::~PaintGUISystem()
{
    delete listeners_[kCanvasClose];
}

PaintGUISystem::PaintGUISystem(Window* window, GUIComponent* root) :
    GUISystem(window, root)
{
    listeners_[kCanvasClose] = new CanvasCloser;
}

void PaintGUISystem::Reset()
{
    for (int i = 0; i < kEventsCount; ++i)
    {
        if (i != kCanvasClose)
        {
            listeners_[i] = nullptr;
        }
    }
}
