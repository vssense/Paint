#ifndef _GUICOMPONENT_SYSTEM_HPP_INCLUDED
#define _GUICOMPONENT_SYSTEM_HPP_INCLUDED

#include "../graphics/window.hpp"
#include "gui_component.hpp"
#include "brush.hpp"

class GUIComponentSystem
{
public:
    GUIComponentSystem(Window* window, GUIComponent* root);

    ~GUIComponentSystem();

    void ProcessEvent(const Event& event);
    void Render(Renderer* renderer);
    Brush& GetBrush();
    void   SetBrush(const Brush& brush);
private:
    void ProcessMouseEvent(Vec2<uint32_t> position, const Event& event);

    Window* window_;
    GUIComponent* root_;
    Brush brush_;
};


#endif /* _GUICOMPONENT_SYSTEM_HPP_INCLUDED */
