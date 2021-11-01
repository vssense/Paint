#ifndef _COMMANDS_HPP_INCLUDED
#define _COMMANDS_HPP_INCLUDED

#include "../gui_component_system/gui_component_commands.hpp"
#include "../gui_component_system/gui_component.hpp"
#include "../graphics/renderer.hpp"
#include "../graphics/texture.hpp"

const uint32_t kTitleWidth = 30;
const uint32_t kButtonsLen = 70;

GUIComponent* CreatePaintTree(Renderer* renderer, bool* is_running);

#endif /* _COMMANDS_HPP_INCLUDED */