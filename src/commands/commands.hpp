#ifndef _COMMANDS_HPP_INCLUDED
#define _COMMANDS_HPP_INCLUDED

#include "../gui_component_system/gui_component_commands.hpp"
#include "../gui_component_system/gui_component.hpp"
#include "../graphics/renderer.hpp"
#include "../graphics/texture.hpp"

const uint32_t kTitleWidth = 30;
const uint32_t kButtonsLen = 70;

GUIComponent* CreatePaintTree(Renderer* renderer, bool* is_running);

GUIComponent* CreateMainWindowTitle(Renderer* renderer, GUIComponent* main_component, bool* is_running, uint32_t len, uint32_t width);
GUIComponent* CreateButton(Renderer* renderer, const char* title, const Rectangle& placement, IOnMouseEventCommand* cmd,
                           uint32_t button_color, uint32_t frame_color = kBlack, uint32_t font_color = kBlack);

GUIComponent* CreateCanvas(Renderer* renderer, const Rectangle& placement);
GUIComponent* CreateCanvasTitle(Renderer* renderer, GUIComponent* canvas, uint32_t len, uint32_t width);

#endif /* _COMMANDS_HPP_INCLUDED */