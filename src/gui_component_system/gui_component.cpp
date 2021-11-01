#include "gui_component.hpp"

GUIComponent::GUIComponent(Texture* texture, Renderer* renderer, IOnMouseEventCommand* on_event, IHitTestCommand* hit_test) :
    texture_(texture), renderer_(renderer), on_event_(on_event), hit_test_(hit_test)
{
    if (on_event_ == nullptr)
    {
        on_event_ = new DefaultOnEventTrue;
    }

    assert(texture_);
    assert(on_event_);
    assert(hit_test_);

    on_event_->SetGUIComponent(this);
}

GUIComponent::GUIComponent(Texture* texture, Renderer* renderer, IOnMouseEventCommand* on_event, const Rectangle& placement) :
    GUIComponent(texture, renderer, on_event, new DefaultHitTest(placement)) {}

GUIComponent::GUIComponent(const char* path, Renderer* renderer, IOnMouseEventCommand* on_event, const Rectangle& placement) :
    GUIComponent(new Texture(renderer, path), renderer, on_event, new DefaultHitTest(placement)) {}

GUIComponent::~GUIComponent()
{
    delete hit_test_;
    delete on_event_;

    for (auto it = children_.Begin(); it != children_.End(); ++it)
    {
         delete (*it);
    }

    delete texture_;
}

Texture* GUIComponent::GetTexture() const
{
    return texture_;
}

Renderer* GUIComponent::GetRenderer() const
{
    return renderer_;
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

    return on_event_->Execute(event);
}

void GUIComponent::AddChild(GUIComponent* component)
{
    assert(component);

    children_.PushBack(component);
}

void GUIComponent::Render(Renderer* renderer, Vec2<uint32_t> position)
{
    Rectangle placement = hit_test_->GetPlaceToRender();
    placement.x0 += position.x;
    placement.y0 += position.y;
    renderer->CopyTexture(texture_, placement);
    for (auto it = children_.Begin(); it != children_.End(); ++it)
    {
        (*it)->Render(renderer, Vec2<uint32_t>(placement.x0, placement.y0));
    }
}