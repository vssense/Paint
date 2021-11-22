#ifndef _LISTENER_HPP_INCLUDED
#define _LISTENER_HPP_INCLUDED

#include "event.hpp"

class IListener
{
public:
    virtual ~IListener() {}
    virtual bool ProcessListenerEvent(const Event& event) = 0;
};

#endif /* _LISTENER_HPP_INCLUDED */