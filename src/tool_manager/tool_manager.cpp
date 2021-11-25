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

void ToolManager::AddTool(ITool* tool)
{
    assert(tool);

    tools_.push_back(tool);
    active_ = tool;
}

void ToolManager::SetActiveTool(ITool* tool)
{
    assert(tool);

    active_ = tool;
}

ITool* ToolManager::GetActiveTool() const
{
    return active_;
}

ToolManager::~ToolManager()
{
    active_ = nullptr;

    for (ITool* tool : tools_)
    {
        delete tool;
    }
}
