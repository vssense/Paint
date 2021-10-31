#ifndef _GUICOMPONENT_HPP_INCLUDED
#define _GUICOMPONENT_HPP_INCLUDED

#include "gui_component_commands.hpp"
#include "../math/vector2.hpp"
#include "../event/event.hpp"
#include "../graphics/texture.hpp"
#include "../graphics/renderer.hpp"
#include "../containers/list.hpp"

class GUIComponent
{
public:
    GUIComponent(Texture* texture, IHitTestCommand* hit_test, IOnEventCommand* on_event);
    ~GUIComponent();

    bool HitTest(Vec2<uint32_t> click);
    bool OnEvent(const Event& event);
    bool OnMove (const Event& event);

    void AddChild(GUIComponent* component);
    void Render(Renderer* renderer);

    Texture* GetTexture() const;
    void     SetTexture(Texture* texture);
private:
    Texture* texture_;
    IHitTestCommand* hit_test_;
    IOnEventCommand* on_event_;

    List<GUIComponent*> children_;
};

#endif /* _GUICOMPONENT_HPP_INCLUDED */