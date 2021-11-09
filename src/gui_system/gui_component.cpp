#include "gui_component.hpp"
#include "default_commands.hpp"

GUIComponent::GUIComponent(Texture* texture, IOnMouseEventCommand* on_event, IHitTestCommand* hit_test) :
    texture_(texture), on_event_(on_event), hit_test_(hit_test)
{
    if (on_event_ == nullptr)
    {
        on_event_ = new DefaultOnEventTrue;
    }

    assert(texture_);
    assert(on_event_);
    assert(hit_test_);

    on_event_->SetGUIComponent(this);
    is_deleted_ = false;
}

GUIComponent::GUIComponent(Texture* texture, IOnMouseEventCommand* on_event, const Rectangle& placement) :
    GUIComponent(texture, on_event, new DefaultHitTest(placement)) {}

GUIComponent::GUIComponent(const char* path, IOnMouseEventCommand* on_event, const Rectangle& placement) :
    GUIComponent(new Texture(path), on_event, new DefaultHitTest(placement)) {}

GUIComponent::~GUIComponent()
{
    delete hit_test_;
    delete on_event_;
    delete texture_;

    for (auto it = children_.begin(); it != children_.end(); ++it)
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

void GUIComponent::Delete()
{
    is_deleted_ = true;
}

bool GUIComponent::IsDeleted()
{
    return is_deleted_;
}

bool GUIComponent::HitTest(Vec2<uint32_t> position)
{
    return hit_test_->Execute(position);
}

bool GUIComponent::OnMouseEvent(Vec2<uint32_t> position, const Event& event, const Vec2<uint32_t> origin)
{
    const Rectangle& placement = hit_test_->GetPlaceToRender();

    Vec2<uint32_t> children_origin(origin);
    children_origin.x += placement.x0;
    children_origin.y += placement.y0;

    if (!HitTest(position - origin))
    {
        return false;
    }

    for (auto it = children_.begin(); it != children_.end(); ++it)
    {
        if ((*it)->OnMouseEvent(position, event, children_origin))
        {
            GUIComponent* processed_event = *it;
            children_.erase(it);
            if (processed_event->IsDeleted())
            {
                delete processed_event;
            }
            else
            {
                AddChild(processed_event);
            }

            return true;
        }
    }

    return on_event_->Execute(event, children_origin);
}

void GUIComponent::AddChild(GUIComponent* component)
{
    assert(component);

    children_.push_front(component);
}

void GUIComponent::Render(Vec2<uint32_t> position)
{
    Renderer* renderer = Renderer::GetInstance();
    Rectangle placement = hit_test_->GetPlaceToRender();
    
    placement.x0 += position.x;
    placement.y0 += position.y;
    renderer->CopyTexture(texture_, placement);

    for (auto it = children_.end(); it != children_.begin();)
    {
        --it;
        (*it)->Render(Vec2<uint32_t>(placement.x0, placement.y0));
    }
}

void GUIComponent::Move(Vec2<int> d)
{
    hit_test_->Move(d);
}