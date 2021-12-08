#include "preferences_panel.hpp"

PreferencesPanel::PreferencesPanel(const Rectangle& placement, Color color)
    : GUIComponent(new Texture(placement.w, placement.h, color, kBlack), placement) {}

void PreferencesPanel::AttachWithCoordinates(GUIComponent* component, Vec2<int> coordinates)
{
    Attach(component);
    component->Move(coordinates);
}

