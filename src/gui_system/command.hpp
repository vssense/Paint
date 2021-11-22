#ifndef _COMMAND_HPP_INCLUDED
#define _COMMAND_HPP_INCLUDED

class ICommand
{
public:
    virtual ~ICommand() {}
    virtual void Execute() = 0;
};

#endif /* _COMMAND_HPP_INCLUDED */