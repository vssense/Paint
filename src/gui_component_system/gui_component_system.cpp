#include "gui_component_system.hpp"

GUIComponentSystem::GUIComponentSystem(Window* window, GUIComponent* root) :
    window_(window), root_(root) {}

GUIComponentSystem::~GUIComponentSystem()
{
    delete root_;
}

void GUIComponentSystem::ProcessMouseEvent(Vec2<uint32_t> position, const Event& event)
{
    root_->OnMouseEvent(position, event);
}

void GUIComponentSystem::Render(Renderer* renderer)
{
    root_->Render(renderer);
}


