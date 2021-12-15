#include "plugin.hpp"
#include <cassert>

namespace plugin
{

IAPI* api = nullptr;

class FlowerTool : public ITool
{
public:
    FlowerTool();
    ~FlowerTool();

    virtual void ActionBegin(ITexture* canvas, int x, int y);
    virtual void Action     (ITexture* canvas, int x, int y, int dx, int dy);
    virtual void ActionEnd  (ITexture* canvas, int x, int y);

    virtual const char* GetIconFileName() const;
    virtual const char* GetName() const override;
    virtual IPreferencesPanel* GetPreferencesPanel() const;

    void SetHeight(int height);
    void SetWidth(int width);

private:
    ITexture* flower_;
    int width_;
    int height_;

    IPreferencesPanel* panel_;

    ILabel* width_label_;
    ILabel* height_label_;

    ISlider* width_slider_;
    ISlider* height_slider_;

    ISliderCallback* width_slider_callback_;
    ISliderCallback* height_slider_callback_;
};

const int kMaxWidth = 100;
const int kMaxHeight = 100;
const int kMaxStrLen = 256;
const int kTabSize = 10;

class SetWidthCallback : public ISliderCallback
{
public:
    SetWidthCallback(FlowerTool* tool) : tool_(tool) {}

    virtual void RespondOnSlide(float old_value, float current_value) override
    {
        tool_->SetWidth(static_cast<int>(current_value * kMaxWidth));
    }

private:
    FlowerTool* tool_;
};

class SetHeightCallback : public ISliderCallback
{
public:
    SetHeightCallback(FlowerTool* tool) : tool_(tool) {}

    virtual void RespondOnSlide(float old_value, float current_value) override
    {
        tool_->SetHeight(static_cast<int>(current_value * kMaxWidth));
    }

private:
    FlowerTool* tool_;
};

const char* FlowerTool::GetName() const
{
    return "Flower";
}

void FlowerTool::SetHeight(int height)
{
    height_ = height;

    char str[kMaxStrLen] = "";
    sprintf(str, "Height: %d", height_);
    height_label_->SetText(str);
}

void FlowerTool::SetWidth(int width)
{
    width_ = width;

    char str[kMaxStrLen] = "";
    sprintf(str, "Width: %d", width_);
    width_label_->SetText(str);
}

FlowerTool::FlowerTool()
    : flower_(nullptr),
      width_(0),
      height_(0),
      panel_(nullptr),
      width_label_(nullptr),
      height_label_(nullptr),
      width_slider_(nullptr),
      height_slider_(nullptr),
      width_slider_callback_(nullptr),
      height_slider_callback_(nullptr)
{
    flower_ = api->GetTextureFactory()->CreateTexture("img/flower.bmp");

    IWidgetFactory* factory = api->GetWidgetFactory();

    width_label_ = factory->CreateDefaultLabel("Width: 0");
    height_label_ = factory->CreateDefaultLabel("Height: 0");

    width_slider_ = factory->CreateDefaultSlider(0, 1);
    height_slider_ = factory->CreateDefaultSlider(0, 1);

    width_slider_callback_ = new SetWidthCallback(this);
    height_slider_callback_ = new SetHeightCallback(this);

    width_slider_->SetSliderCallback(width_slider_callback_);
    height_slider_->SetSliderCallback(height_slider_callback_);

    panel_ = factory->CreateDefaultPreferencesPanel();

    int height = kTabSize;

    panel_->Attach(width_label_, kTabSize, height);
    height += kTabSize + width_label_->GetHieght();

    panel_->Attach(width_slider_, kTabSize, height);
    height += kTabSize + width_slider_->GetHieght();

    panel_->Attach(height_label_, kTabSize, height);
    height += kTabSize + height_label_->GetHieght();

    panel_->Attach(height_slider_, kTabSize, height);
}

FlowerTool::~FlowerTool()
{
    delete flower_;
    delete panel_;
    delete width_label_;
    delete height_label_;
    delete width_slider_;
    delete height_slider_;
    delete width_slider_callback_;
    delete height_slider_callback_;
}

void FlowerTool::ActionBegin(ITexture* canvas, int x, int y)
{
    assert(canvas);

    canvas->CopyTexture(flower_, x - width_ / 2, y - height_ / 2, width_, height_);
}

void FlowerTool::Action(ITexture* canvas, int x, int y, int dx, int dy)
{
    assert(canvas);

    canvas->CopyTexture(flower_, x - width_ / 2, y - height_ / 2, width_, height_);
}

void FlowerTool::ActionEnd(ITexture* canvas, int x, int y)
{
    assert(canvas);


    canvas->CopyTexture(flower_, x - width_ / 2, y - height_ / 2, width_, height_);
}

const char* FlowerTool::GetIconFileName() const
{
    return "img/flower.bmp";
}

IPreferencesPanel* FlowerTool::GetPreferencesPanel() const
{
    return panel_;
}

class Plugin : public IPlugin
{
public:
    Plugin(FlowerTool* flower_tool)
        : flower_tool_(flower_tool) {}

    ~Plugin();

    virtual std::list<IFilter*> GetFilters() const override;
    virtual std::list<ITool*>   GetTools  () const override;

private:
    FlowerTool* flower_tool_;
};

Plugin::~Plugin()
{
    delete flower_tool_;
}

std::list<IFilter*> Plugin::GetFilters() const
{
    return std::list<IFilter*>();
}

std::list<ITool*> Plugin::GetTools() const
{
    std::list<ITool*> list;
    list.push_back(flower_tool_);

    return list;
}

extern "C" IPlugin* Create(IAPI* api)
{
    plugin::api = api;
    return new Plugin(new FlowerTool);
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