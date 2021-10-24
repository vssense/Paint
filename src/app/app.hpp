#ifndef _APP_HPP_INCLUDED
#define _APP_HPP_INCLUDED

#include "../graphics/coordinate_system.hpp"
#include "../graphics/renderer.hpp"
#include "../graphics/text.hpp"
#include "../graphics/window.hpp"
#include "../event/event.hpp"

const float kCoordinateSystemWidth  = 100;
const float kCoordinateSystemHeight = 100;

class App
{
public:
    App() {}
    ~App() {}
    void operator () ();
};

#endif /* _APP_HPP_INCLUDED */