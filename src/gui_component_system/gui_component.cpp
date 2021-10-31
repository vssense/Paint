#include "gui_component.hpp"

GUIComponent::GUIComponent(Texture* texture, IOnMouseEventCommand* on_event, IHitTestCommand* hit_test) :
    texture_(texture), hit_test_(hit_test), on_event_(on_event) {}

GUIComponent::~GUIComponent()
{
    delete hit_test_;
    delete on_event_;

    for (auto it = children_.Begin(); it != children_.End(); ++it)
    {
         delete (*it);
    }
}

Texture* GUIComponent::GetTexture() const
{
    return texture_;
}

void GUIComponent::SetTexture(Texture* texture)
{
    texture_ = texture;
}

bool GUIComponent::HitTest(Vec2<uint32_t> position)
{
    return hit_test_->Execute(position);
}

bool GUIComponent::OnMouseEvent(Vec2<uint32_t> position, const Event& event)
{
    if (!HitTest(position))
    {
        return false;
    }

    for (auto it = children_.Begin(); it != children_.End(); ++it)
    {
        if ((*it)->OnMouseEvent(position, event))
        {
            return true;
        }
    }

    return on_event_->Execute(position, event);
}

void GUIComponent::AddChild(GUIComponent* component)
{
    assert(component);

    children_.PushBack(component);
}

void GUIComponent::Render(Renderer* renderer)
{
    renderer->CopyTexture(texture_, hit_test_->GetPlaceToRender());
    for (auto it = children_.Begin(); it != children_.End(); ++it)
    {
        (*it)->Render(renderer);
    }
}