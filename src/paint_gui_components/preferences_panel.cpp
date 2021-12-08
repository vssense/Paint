#include "preferences_panel.hpp"
#include "../paint_gui_components/paint_main_component.hpp"

PreferencesPanel::PreferencesPanel(const Rectangle& placement, Color color)
    : GUIComponent(new Texture(placement.w, placement.h, color, kBlack), placement)
{
    Attach(new Button(Rectangle{placement_.w - kTitleWidth, 0, kTitleWidth, kTitleWidth},
                     new UnpinComponent(this), new Texture("img/close.bmp"),
                     new Texture("img/close2.bmp")));
}

void PreferencesPanel::AttachWithCoordinates(GUIComponent* component, Vec2<int> coordinates)
{
    Attach(component);
    component->Move(coordinates);
}

bool PreferencesPanel::ProcessMouseEvent(const Event& event)
{
    switch (event.GetType())
    {
        case kMouseButtonPress:
        {
            system_->Subscribe(this, kMouseMotion);
            system_->Subscribe(this, kMouseButtonRelease);
            break;
        }
        default:
        {
            break;
        }
    }

    return true;
}

bool PreferencesPanel::ProcessListenerEvent(const Event& event)
{
    switch (event.GetType())
    {
        case kMouseMotion:
        {
            Move(event.GetValue().mouse.d);
            break;
        }
        case kMouseButtonRelease:
        {
            system_->Unsubscribe(kMouseButtonRelease);
            system_->Unsubscribe(kMouseMotion);
            break;
        }
        default:
        {
            break;
        }
    }

    return true;
}

