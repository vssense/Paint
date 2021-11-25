#ifndef _TOOL_MANAGER_HPP_INCLUDED
#define _TOOL_MANAGER_HPP_INCLUDED

#include "tool.hpp"
#include <vector>

typedef plugin::ITool ITool;

class ToolManager
{
private:
    ToolManager();
public:
    static ToolManager* GetInstance();
    ~ToolManager();

    void AddTool(ITool* tool);
    void SetActiveTool(ITool* tool);
    ITool* GetActiveTool() const;

private:
    ITool* active_;
    
    std::vector<ITool*> tools_;
    static ToolManager* instance_;
};

#endif /* _TOOL_MANAGER_HPP_INCLUDED */