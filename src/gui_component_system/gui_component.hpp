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
    GUIComponent(Texture* texture, IOnMouseEventCommand* on_event, IHitTestCommand* hit_test);
    ~GUIComponent();

    bool HitTest(Vec2<uint32_t> position);
    bool OnMouseEvent(Vec2<uint32_t> position, const Event& event);

    void AddChild(GUIComponent* component);
    void Render(Renderer* renderer);

    Texture* GetTexture() const;
    void     SetTexture(Texture* texture);
private:
    Texture* texture_;
    IHitTestCommand* hit_test_;
    IOnMouseEventCommand* on_event_;

    List<GUIComponent*> children_;
};

#endif /* _GUICOMPONENT_HPP_INCLUDED */