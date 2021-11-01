#ifndef _CLOSE_COMMANDS_HPP_INCLUDED
#define _CLOSE_COMMANDS_HPP_INCLUDED

#include "../gui_component_system/gui_component_commands.hpp"

class MainCloseOnMouseEvent : public IOnMouseEventCommand
{
public:
    MainCloseOnMouseEvent(bool* is_running) : is_running_(is_running) { assert(is_running_); }
    virtual bool Execute(const Event& event) override
    {
        if (event.GetType() == kMouseButtonRelease)
        {
            *is_running_ = false;
        }

        return true;
    }

private:
    bool* is_running_;
};

#endif /* _CLOSE_COMMANDS_HPP_INCLUDED */
