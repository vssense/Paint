#ifndef _GUI_SYSTEM_HPP_INCLUDED
#define _GUI_SYSTEM_HPP_INCLUDED

#include "../graphics/window.hpp"
#include "gui_component.hpp"

class GUISystem
{
public:
    GUISystem(Window* window, GUIComponent* root);

    virtual ~GUISystem();

    void ProcessEvent(const Event& event);
    void Render();
private:
    void ProcessMouseEvent(Vec2<uint32_t> position, const Event& event);

    Window* window_;
    GUIComponent* root_;
};


#endif /* _GUI_SYSTEM_HPP_INCLUDED */
