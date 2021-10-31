#include "gui_component_system.hpp"

GUIComponentSystem::GUIComponentSystem(Window* window, GUIComponent* root) :
    window_(window), root_(root) {}

GUIComponentSystem::~GUIComponentSystem() {}

void GUIComponentSystem::ProcessEvent(const Event& event)
{
    root_->OnEvent(event);
}

void GUIComponentSystem::Render(Renderer* renderer)
{
    root_->Render(renderer);
}


