#include "gui_component.hpp"

GUIComponent::GUIComponent(Texture* texture, IHitTestCommand* hit_test, IOnEventCommand* on_event) :
    texture_(texture), hit_test_(hit_test), on_event_(on_event) {}

GUIComponent::~GUIComponent()
{
    // delete hit_test_;
    // delete on_event_;
}

Texture* GUIComponent::GetTexture() const
{
    return texture_;
}

void GUIComponent::SetTexture(Texture* texture)
{
    texture_ = texture;
}

bool GUIComponent::HitTest(Vec2<uint32_t> click)
{
    return hit_test_->Execute(click);
}

bool GUIComponent::OnEvent(const Event& event)
{
    switch (event.GetType())
    {
        case kMouseButtonPress:
        case kMouseButtonRelease:
            if (!HitTest(event.GetValue().coordinates))
            {
                return false;
            }

            break;
        case kMouseMotion:
            if (!HitTest(event.GetValue().motion.start))
            {
                return false;
            }

            break;
        default:
            return true;        
    }

    for (auto it = children_.Begin(); it != children_.End(); ++it)
    {
        if ((*it)->OnEvent(event))
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

void GUIComponent::Render(Renderer* renderer)
{
    renderer->CopyTexture(texture_, hit_test_->GetPlaceToRender());
}