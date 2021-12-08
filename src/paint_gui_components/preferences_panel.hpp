#ifndef _PREFERENCES_PANEL_HPP_INCLUDED
#define _PREFERENCES_PANEL_HPP_INCLUDED

#include "../gui_system/gui_component.hpp"

const int kDefaultPreferencesPanelWidth  = 300;
const int kDefaultPreferencesPanelHeight = 500;

const Rectangle kDefaultPreferencesPanelPlacement = 
    Rectangle{kWindowWidth  / 2 - kDefaultPreferencesPanelWidth  / 2,
              kWindowHeight / 2 - kDefaultPreferencesPanelHeight / 2,
              kDefaultPreferencesPanelWidth,
              kDefaultPreferencesPanelHeight};

class PreferencesPanel : public GUIComponent
{
public:
    PreferencesPanel(const Rectangle& placement = kDefaultPreferencesPanelPlacement, Color color = kLightPurple);

    void AttachWithCoordinates(GUIComponent* component, Vec2<int> coordinates);
};

#endif /* _PREFERENCES_PANEL_HPP_INCLUDED */