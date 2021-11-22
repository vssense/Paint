#ifndef _GUICOMPONENT_HPP_INCLUDED
#define _GUICOMPONENT_HPP_INCLUDED

#include "../math/vector2.hpp"
#include "../event/event.hpp"
#include "../event/listener.hpp"
#include "../graphics/texture.hpp"
#include "../graphics/renderer.hpp"
#include <list>

class GUISystem;

class GUIComponent : public IListener
{
public:
    GUIComponent(Texture* texture, const Rectangle& relative_placement);
    virtual ~GUIComponent();

    virtual bool HitTest(Vec2<int> coordinates) const;
    virtual bool OnMouseEvent(const Event& event);
    virtual bool ProcessMouseEvent(const Event& event);
    virtual bool ProcessListenerEvent(const Event& event) override;

    virtual void Move(Vec2<int> d);
    virtual void Render();
 
    void Attach(GUIComponent* component);
    void Detach(GUIComponent* component);
    void SetGUISystem(GUISystem* system);

    GUIComponent* GetParent() const;
    GUISystem* GetSystem();

protected:
    Texture* texture_;
    Rectangle placement_;

    GUIComponent* parent_;
    GUISystem* system_;
    std::list<GUIComponent*> children_;
};

class Bagel : public GUIComponent
{
public:
    Bagel(Vec2<int> center, uint32_t r1, uint32_t r2, Color color);

    virtual bool ProcessMouseEvent   (const Event& event) override;
    virtual bool ProcessListenerEvent(const Event& event) override;
    virtual bool HitTest(Vec2<int> coordinates) const override;

    virtual void Move(Vec2<int> d) override;

protected:
    Vec2<int> center_;
    uint32_t r1_;
    uint32_t r2_;
};

#endif /* _GUICOMPONENT_HPP_INCLUDED */
