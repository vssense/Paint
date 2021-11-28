#include "plugin.hpp"
#include <cassert>

namespace plugin
{

IAPI* api = nullptr;

class SquareTool : public ITool
{
public:
    SquareTool() {}

    virtual void ActionBegin(ITexture* canvas, int x, int y);
    virtual void Action     (ITexture* canvas, int x, int y, int dx, int dy);
    virtual void ActionEnd  (ITexture* canvas, int x, int y);

    virtual const char* GetIconFileName() const;
    virtual IPreferencesPanel* GetPreferencesPanel() const;
};

void SquareTool::ActionBegin(ITexture* canvas, int x, int y)
{
    assert(canvas);

    canvas->DrawRect(x, y, 20, 20, 0xFF'00'00'00);
}

void SquareTool::Action(ITexture* canvas, int x, int y, int dx, int dy)
{
    assert(canvas);

    canvas->DrawRect(x, y, 20, 20, 0xFF'00'00'00);
}

void SquareTool::ActionEnd(ITexture* canvas, int x, int y)
{
    assert(canvas);

    canvas->DrawRect(x, y, 20, 20, 0xFF'00'00'00);
}

const char* SquareTool::GetIconFileName() const
{
    return "Square2";
}

IPreferencesPanel* SquareTool::GetPreferencesPanel() const
{
    return nullptr;
}

class Plugin : public IPlugin
{
public:
    Plugin(SquareTool* square_tool)
        : square_tool_(square_tool) {}

    ~Plugin();

    virtual std::list<IFilter*> GetFilters() const override;
    virtual std::list<ITool*>   GetTools  () const override;

private:
    SquareTool* square_tool_;
};

Plugin::~Plugin()
{
    delete square_tool_;
}

std::list<IFilter*> Plugin::GetFilters() const
{
    return std::list<IFilter*>();
}

std::list<ITool*> Plugin::GetTools() const
{
    std::list<ITool*> list;
    list.push_back(square_tool_);

    return list;
}

extern "C" IPlugin* Create(IAPI* api)
{
    plugin::api = api;
    return new Plugin(new SquareTool);
}

extern "C" void Destroy(IPlugin* plugin)
{
    delete plugin;
}

extern "C" uint32_t Version()
{
    return kVersion;
}

}