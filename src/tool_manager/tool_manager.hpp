#ifndef _TOOL_MANAGER_HPP_INCLUDED
#define _TOOL_MANAGER_HPP_INCLUDED

#include "tool.hpp"
#include <vector>

class ToolManager
{
private:
    ToolManager();
public:
    static ToolManager* GetInstance();
    ~ToolManager();

    void AddTool(Tool* tool);
    void SetActiveTool(Tool* tool);
    Tool* GetActiveTool() const;

private:
    Tool* active_;
    
    std::vector<Tool*> tools_;
    static ToolManager* instance_;
};

#endif /* _TOOL_MANAGER_HPP_INCLUDED */