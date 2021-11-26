#ifndef _APP_HPP_INCLUDED
#define _APP_HPP_INCLUDED

#include "../graphics/renderer.hpp"
#include "../graphics/text.hpp"
#include "../graphics/window.hpp"
#include "../event/event.hpp"
#include "../paint_gui_system/paint_gui_system.hpp"
#include "../paint_gui_components/paint_main_component.hpp"
#include "../tool_manager/tool_manager.hpp"
#include "../tool_manager/brush.hpp"

class App
{
public:
    App() {}
    ~App() {}
    void operator()();
};

#endif /* _APP_HPP_INCLUDED */
