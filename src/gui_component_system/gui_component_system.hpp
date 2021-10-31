#ifndef _GUICOMPONENT_SYSTEM_HPP_INCLUDED
#define _GUICOMPONENT_SYSTEM_HPP_INCLUDED

#include "../graphics/window.hpp"
#include "gui_component.hpp"

class GUIComponentSystem
{
public:
    GUIComponentSystem(Window* window, GUIComponent* root);

    ~GUIComponentSystem();

    void ProcessEvent(const Event& event);
    void Render(Renderer* renderer);

private:
    void ProcessMouseEvent(Vec2<uint32_t> position, const Event& event);

    Window* window_;
    GUIComponent* root_;
};


#endif /* _GUICOMPONENT_SYSTEM_HPP_INCLUDED */
