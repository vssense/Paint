#ifndef _PREFERENCES_PANEL_HPP_INCLUDED
#define _PREFERENCES_PANEL_HPP_INCLUDED

#include "../gui_system/gui_component.hpp"
#include "../gui_system/button.hpp"

const int kDefaultPreferencesPanelWidth  = 300;
const int kDefaultPreferencesPanelHeight = 400;
const int kTabSize = 10;

const Rectangle kDefaultPreferencesPanelPlacement = 
    Rectangle{kWindowWidth  / 2 - kDefaultPreferencesPanelWidth  / 2,
              kWindowHeight / 2 - kDefaultPreferencesPanelHeight / 2,
              kDefaultPreferencesPanelWidth,
              kDefaultPreferencesPanelHeight};

class PreferencesPanel : public GUIComponent
{
public:
    PreferencesPanel(const Rectangle& placement = kDefaultPreferencesPanelPlacement, Color color = kLightPurple);

    virtual bool ProcessMouseEvent(const Event& event) override;
    virtual bool ProcessListenerEvent(const Event& event) override;

    void AttachWithCoordinates(GUIComponent* component, Vec2<int> coordinates);
};

#endif /* _PREFERENCES_PANEL_HPP_INCLUDED */