#ifndef _GUICOMPONENT_HPP_INCLUDED
#define _GUICOMPONENT_HPP_INCLUDED

#include "../math/vector2.hpp"
#include "../event/event.hpp"
#include "../graphics/texture.hpp"
#include "../graphics/renderer.hpp"
#include <list>

class GUIComponent
{
public:
    GUIComponent(Texture* texture, const Rectangle& relative_placement);
    virtual ~GUIComponent();

    virtual bool HitTest     (Vec2<uint32_t> coordinates) const;
    virtual bool OnMouseEvent(Vec2<uint32_t> coordinates, const Event& event);
    virtual bool ProcessMouseEvent(const Event& event);

    virtual void Move(Vec2<int32_t> d);
    virtual void Render();
    void Attach(GUIComponent* component);

    void Delete();
    bool IsDeleted() const;

    // const Rectangle& GetPlacement();

    // void SetParent();
    // GUIComponent* GetParent();

protected:
    Texture* texture_;
    Rectangle placement_;

    bool is_deleted_;
    GUIComponent* parent_;
    std::list<GUIComponent*> children_; 
};

#endif /* _GUICOMPONENT_HPP_INCLUDED */