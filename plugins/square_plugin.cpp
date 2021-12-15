#include "plugin.hpp"
#include <cassert>
#include <cstdio>

namespace plugin
{

const uint32_t kDefaultThickness = 10;
const uint32_t kMaxThickness = 100;

IAPI* api = nullptr;
const int kMaxStrLen = 256;

class SquareTool : public ITool
{
public:
    SquareTool();
    ~SquareTool();

    virtual void ActionBegin(ITexture* canvas, int x, int y) override;
    virtual void Action     (ITexture* canvas, int x, int y, int dx, int dy) override;
    virtual void ActionEnd  (ITexture* canvas, int x, int y) override;

    virtual const char* GetIconFileName() const override;
    virtual IPreferencesPanel* GetPreferencesPanel() const override;

    Color    GetColor()     const;
    uint32_t GetThickness() const;

    void SetColor(Color color);
    void SetThickness(uint32_t thickness);

private:
    IPreferencesPanel* panel_;
    
    ILabel* thickness_label_;
    ISlider* thickness_slider_;
    ISliderCallback* callback_;

    ILabel* color_label_;
    ISlider* color_slider_r;
    ISlider* color_slider_g;
    ISlider* color_slider_b;
    ISliderCallback* color_callback_r;
    ISliderCallback* color_callback_g;
    ISliderCallback* color_callback_b;

    Color color_;
    uint32_t thickness_;
};

Color SquareTool::GetColor() const
{
    return color_;
}

uint32_t SquareTool::GetThickness() const
{
    return thickness_;
}

void SquareTool::SetColor(Color color)
{
    color_ = color;

    char str[kMaxStrLen] = "";
    sprintf(str, "Color: 0x%u'%u'%u", color_ & 0xFF, (color_ >> 8) & 0xFF,
                                     (color_ >> 16) & 0xFF);
    color_label_->SetText(str);
}

void SquareTool::SetThickness(uint32_t thickness)
{
    thickness_ = thickness;

    char str[kMaxStrLen] = "";
    sprintf(str, "Thickness: %u", thickness);
    thickness_label_->SetText(str);
}

class ThicknessSliderCallback : public ISliderCallback
{
public:
    ThicknessSliderCallback(SquareTool* tool) : tool_(tool) {}

    virtual void RespondOnSlide(float old_value, float current_value) override
    {
        tool_->SetThickness(static_cast<uint32_t>(current_value * kMaxThickness));
    }

private:
    SquareTool* tool_;
};

class ColorRSliderCallback : public ISliderCallback
{
public:
    ColorRSliderCallback(SquareTool* tool) : tool_(tool) {}

    virtual void RespondOnSlide(float old_value, float current_value) override
    {
        Color color = tool_->GetColor();
        color = color & 0xFF00FFFF;
        color = (color | static_cast<uint32_t>(current_value * 0xFF) << 16);
        tool_->SetColor(color);
    }

private:
    SquareTool* tool_;
};

class ColorGSliderCallback : public ISliderCallback
{
public:
    ColorGSliderCallback(SquareTool* tool) : tool_(tool) {}

    virtual void RespondOnSlide(float old_value, float current_value) override
    {
        Color color = tool_->GetColor();
        color = color &  0xFFFF00FF;
        color = (color | static_cast<uint32_t>(current_value * 0xFF) << 8);
        tool_->SetColor(color);
    }

private:
    SquareTool* tool_;
};

class ColorBSliderCallback : public ISliderCallback
{
public:
    ColorBSliderCallback(SquareTool* tool) : tool_(tool) {}

    virtual void RespondOnSlide(float old_value, float current_value) override
    {
        Color color = tool_->GetColor();
        color = (color & 0xFFFFFF00) | static_cast<uint32_t>(current_value * 0xFF);
        tool_->SetColor(color);
    }

private:
    SquareTool* tool_;
};

const int kTabSize = 10;

SquareTool::SquareTool()
    : panel_(nullptr),

      thickness_label_(nullptr),
      thickness_slider_(nullptr),
      callback_(nullptr),

      color_label_(nullptr),

      color_slider_r(nullptr),
      color_slider_g(nullptr),
      color_slider_b(nullptr),
      color_callback_r(nullptr),
      color_callback_g(nullptr),
      color_callback_b(nullptr),
      
      color_(0xFF'00'00'00),
      thickness_(kDefaultThickness)
{
    if (api == nullptr)
    {
        return;
    }

    IWidgetFactory* factory = api->GetWidgetFactory();
    panel_ = factory->CreateDefaultPreferencesPanel();

    int width = panel_->GetWidth();

    thickness_label_ = factory->CreateDefaultLabel("Thickness: 0");
    thickness_slider_ = factory->CreateDefaultSlider(0, 1);
    callback_ = new ThicknessSliderCallback(this);
    thickness_slider_->SetSliderCallback(callback_);

    int height = kTabSize;

    panel_->Attach(thickness_label_, kTabSize, height);
    height += thickness_label_->GetHieght() + kTabSize;

    panel_->Attach(thickness_slider_, (width - thickness_slider_->GetWidth()) / 2, kTabSize * 2 +
                   thickness_label_->GetHieght());
    height += thickness_slider_->GetHieght() + kTabSize;

    color_label_ = factory->CreateDefaultLabel("Color: 0x00'00'00");

    callback_ = new ThicknessSliderCallback(this);

    color_slider_r = factory->CreateDefaultSlider(0, 1);
    color_callback_r = new ColorRSliderCallback(this);
    color_slider_r->SetSliderCallback(color_callback_r);
    
    color_slider_g = factory->CreateDefaultSlider(0, 1);
    color_callback_g = new ColorGSliderCallback(this);
    color_slider_g->SetSliderCallback(color_callback_g);
    
    color_slider_b = factory->CreateDefaultSlider(0, 1);
    color_callback_b = new ColorBSliderCallback(this);
    color_slider_b->SetSliderCallback(color_callback_b);    

    panel_->Attach(color_label_, kTabSize, height);
    height += color_label_->GetHieght() + kTabSize;

    panel_->Attach(color_slider_r, (width - color_slider_r-> GetWidth()) / 2, height);
    height += color_slider_r->GetHieght() + kTabSize;

    panel_->Attach(color_slider_g, (width - color_slider_g-> GetWidth()) / 2, height);
    height += color_slider_g->GetHieght() + kTabSize;

    panel_->Attach(color_slider_b, (width - color_slider_b-> GetWidth()) / 2, height);
}

SquareTool::~SquareTool()
{
    delete panel_;
    
    delete thickness_slider_;
    delete callback_;
    
    delete color_label_;
    delete color_slider_r;
    delete color_slider_g;
    delete color_slider_b;
    delete color_callback_r;
    delete color_callback_g;
    delete color_callback_b;
}

void SquareTool::ActionBegin(ITexture* canvas, int x, int y)
{
    assert(canvas);

    canvas->DrawRect(x, y, thickness_, thickness_, color_);
}

void SquareTool::Action(ITexture* canvas, int x, int y, int dx, int dy)
{
    assert(canvas);

    canvas->DrawRect(x, y, thickness_, thickness_, color_);
}

void SquareTool::ActionEnd(ITexture* canvas, int x, int y)
{
    assert(canvas);

    canvas->DrawRect(x, y, thickness_, thickness_, color_);
}

const char* SquareTool::GetIconFileName() const
{
    return "img/square.bmp";
}

IPreferencesPanel* SquareTool::GetPreferencesPanel() const
{
    return panel_;
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