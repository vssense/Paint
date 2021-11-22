#include "tool_manager.hpp"

ToolManager* ToolManager::instance_ = nullptr;

ToolManager::ToolManager() :
    active_(nullptr) {}

ToolManager* ToolManager::GetInstance()
{
    if (instance_ == nullptr)
    {
        instance_ = new ToolManager;
        assert(instance_);
    }

    return instance_;
}

void ToolManager::AddTool(Tool* tool)
{
    assert(tool);

    tools_.push_back(tool);
    active_ = tool;
}

void ToolManager::SetActiveTool(Tool* tool)
{
    assert(tool);

    active_ = tool;
}

Tool* ToolManager::GetActiveTool() const
{
    return active_;
}

ToolManager::~ToolManager()
{
    active_ = nullptr;

    for (Tool* tool : tools_)
    {
        delete tool;
    }
}
