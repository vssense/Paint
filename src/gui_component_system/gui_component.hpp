#ifndef _GUICOMPONENT_HPP_INCLUDED
#define _GUICOMPONENT_HPP_INCLUDED

#include "gui_component_commands.hpp"
#include "../math/vector2.hpp"
#include "../event/event.hpp"
#include "../graphics/texture.hpp"
#include "../graphics/renderer.hpp"
#include "../containers/list.hpp"
#include <list>

class GUIComponent
{
public:
    GUIComponent(Texture* texture, Renderer* renderer, IOnMouseEventCommand* on_event, IHitTestCommand* hit_test);
    GUIComponent(Texture* texture, Renderer* renderer, IOnMouseEventCommand* on_event, const Rectangle& placement);
    GUIComponent(const char* path, Renderer* renderer, IOnMouseEventCommand* on_event, const Rectangle& placement);
    ~GUIComponent();

    bool HitTest(Vec2<uint32_t> position);
    bool OnMouseEvent(Vec2<uint32_t> position, const Event& event, Vec2<uint32_t> origin);

    void AddChild(GUIComponent* component);
    void Render(Renderer* renderer, Vec2<uint32_t> position);
    void Move(Vec2<int> d);

    Texture* GetTexture () const;
    Renderer* GetRenderer() const;
    void SetTexture(Texture* texture);
    void Delete();
    bool IsDeleted();

private:
    Texture* texture_;
    Renderer* renderer_;
    IOnMouseEventCommand* on_event_;
    IHitTestCommand* hit_test_;

    bool is_deleted_;
    std::list<GUIComponent*> children_;
};

#endif /* _GUICOMPONENT_HPP_INCLUDED */