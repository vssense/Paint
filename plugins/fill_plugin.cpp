#include "plugin.hpp"

#include <cassert>
#include <queue>
#include <vector>

namespace plugin
{

IAPI* api = nullptr;

class FillTool : public ITool
{
public:
    FillTool();
    ~FillTool();

    virtual void ActionBegin(ITexture* canvas, int x, int y);
    virtual void Action     (ITexture* canvas, int x, int y, int dx, int dy);
    virtual void ActionEnd  (ITexture* canvas, int x, int y);

    virtual const char* GetIconFileName() const;
    virtual IPreferencesPanel* GetPreferencesPanel() const;

private:
    Color color_;

    IPreferencesPanel* panel_;
};

FillTool::FillTool()
    : color_(0xFF'00'00'00),
      panel_(nullptr)
{

}

FillTool::~FillTool()
{

}

struct Point
{
    int x;
    int y;
};

Color ToBuffer(Color color)
{
    Color buf_color = 0;
    buf_color |= (color & 0xFF'00'00'00) >> 24;
    buf_color |= (color & 0x00'FF'00'00) >> 8;
    buf_color |= (color & 0x00'00'FF'00) << 8;
    buf_color |= (color & 0x00'00'00'FF) << 24;
    return buf_color;
}

void FillTool::ActionBegin(ITexture* canvas, int x, int y)
{
    assert(canvas);

    Buffer buffer = canvas->ReadBuffer();
    int width = canvas->GetWidth();
    int height = canvas->GetHieght();

    std::vector<std::vector<bool>> used(width, std::vector<bool>(height, false));
    std::queue<Point> queue;
    queue.push(Point{x, y});

    while (!queue.empty())
    {
        Point cur = queue.front();
        queue.pop();

        used[cur.x][cur.y] = true;
        Color prev = buffer.pixels[cur.x + cur.y * width];
        buffer.pixels[cur.x + cur.y * width] = ToBuffer(color_);

        if (cur.x + 1 < width && !used[cur.x + 1][cur.y] &&
            buffer.pixels[cur.x + 1 + cur.y * width] == prev)
        {
            used[cur.x + 1][cur.y] = true;
            queue.push({cur.x + 1, cur.y});
        }

        if (cur.x - 1 > 0 && !used[cur.x - 1][cur.y] &&
            buffer.pixels[cur.x - 1 + cur.y * width] == prev)
        {
            used[cur.x - 1][cur.y] = true;
            queue.push({cur.x - 1, cur.y});
        }

        if (cur.y + 1 < height && !used[cur.x][cur.y + 1] &&
            buffer.pixels[cur.x + (cur.y + 1) * width] == prev)
        {
            used[cur.x][cur.y + 1] = true;
            queue.push({cur.x, cur.y + 1});
        }

        if (cur.y - 1 > 0 && !used[cur.x][cur.y - 1] &&
            buffer.pixels[cur.x + (cur.y - 1) * width] == prev)
        {
            used[cur.x][cur.y - 1] = true;
            queue.push({cur.x, cur.y - 1});
        }
    }

    canvas->LoadBuffer(buffer);
    canvas->ReleaseBuffer(buffer);
}

void FillTool::Action(ITexture* canvas, int x, int y, int dx, int dy)
{
    assert(canvas);
}

void FillTool::ActionEnd(ITexture* canvas, int x, int y)
{
    assert(canvas);
}

const char* FillTool::GetIconFileName() const
{
    return "img/fill.bmp";
}

IPreferencesPanel* FillTool::GetPreferencesPanel() const
{
    return panel_;
}

class Plugin : public IPlugin
{
public:
    Plugin(FillTool* fill_tool)
        : fill_tool_(fill_tool) {}

    ~Plugin();

    virtual std::list<IFilter*> GetFilters() const override;
    virtual std::list<ITool*>   GetTools  () const override;

private:
    FillTool* fill_tool_;
};

Plugin::~Plugin()
{
    delete fill_tool_;
}

std::list<IFilter*> Plugin::GetFilters() const
{
    return std::list<IFilter*>();
}

std::list<ITool*> Plugin::GetTools() const
{
    std::list<ITool*> list;
    list.push_back(fill_tool_);

    return list;
}

extern "C" IPlugin* Create(IAPI* api)
{
    plugin::api = api;
    return new Plugin(new FillTool);
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