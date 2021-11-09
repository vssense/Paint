#ifndef _COMMANDS_HPP_INCLUDED
#define _COMMANDS_HPP_INCLUDED

#include "../paint_gui_system/paint_gui_system.hpp"
#include "../gui_system/gui_component.hpp"
#include "../gui_system/gui_component_commands.hpp"
#include "../graphics/renderer.hpp"
#include "../graphics/texture.hpp"

const uint32_t kTitleWidth = 30;
const uint32_t kButtonsLen = 70;
const uint32_t kColorSquareSize = 20;
const Rectangle kPalettePlacement{100, 100, 70, 100};

GUIComponent* CreatePaintTree(bool* is_running, PaintGUISystem* system);

GUIComponent* CreateMainWindowTitle(GUIComponent* main_component, bool* is_running, uint32_t len, uint32_t width, PaintGUISystem* system);
GUIComponent* CreateButton         (const char* title, const Rectangle& placement, IOnMouseEventCommand* cmd,
                                    uint32_t button_color, uint32_t frame_color = kBlack, uint32_t font_color = kBlack);

GUIComponent* CreateCanvas      (const Rectangle& placement, PaintGUISystem* system);
GUIComponent* CreateCanvasTitle (GUIComponent* canvas, uint32_t len, uint32_t width);
GUIComponent* CreateScene       (const Rectangle& placement, PaintGUISystem* system);
GUIComponent* CreatePalette     (const Rectangle& placement, PaintGUISystem* system);
GUIComponent* CreatePaletteColor(const Rectangle& placement, uint32_t color,
                                 PaintGUISystem* system);

#endif /* _COMMANDS_HPP_INCLUDED */
