#ifndef _APP_HPP_INCLUDED
#define _APP_HPP_INCLUDED

#include "../graphics/renderer.hpp"
#include "../graphics/text.hpp"
#include "../graphics/window.hpp"
#include "../event/event.hpp"
#include "../paint_gui_system/paint_gui_system.hpp"

class App
{
public:
    App() {}
    ~App() {}
    void operator () ();
};

#endif /* _APP_HPP_INCLUDED */