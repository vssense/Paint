#ifndef _PLUGIN_HPP_INCLUDED_
#define _PLUGIN_HPP_INCLUDED_

#include <cstdint>
#include <list>
#include <iostream>

namespace plugin {

const uint32_t kVersion = 1;
typedef uint32_t Color; // RGBA8888
    
class ITexture;

struct Buffer {
    Color* pixels;
    ITexture* texture;
};

class ITexture {
  public:
    virtual ~ITexture() {}

    virtual int32_t GetWidth() = 0;
    virtual int32_t GetHieght() = 0;

    virtual Buffer ReadBuffer() = 0;
    virtual void   ReleaseBuffer(Buffer buffer) = 0;
    virtual void   LoadBuffer(Buffer buffer) = 0;

    virtual void Clear(Color color) = 0;
    virtual void Present() = 0;

    virtual void DrawLine     (int32_t x0, int32_t y0, int32_t x1, int32_t y1, Color color) = 0;
    virtual void DrawThickLine(int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t thickness, Color color) = 0;
    virtual void DrawCircle   (int32_t x,  int32_t y,  int32_t radius, Color color) = 0;
    virtual void DrawRect     (int32_t x,  int32_t y,  int32_t width, int32_t height, Color color) = 0;

    virtual void CopyTexture(ITexture* texture, int32_t x, int32_t y, int32_t width, int32_t height) = 0;
};

class ITextureFactory {
  public:
    virtual ~ITextureFactory() {}

    virtual ITexture* CreateTexture(const char* filename) = 0;
    virtual ITexture* CreateTexture(int32_t width, int32_t height) = 0;
};

class IClickCallback {
  public:
    virtual ~IClickCallback() {}

    virtual void RespondOnClick() = 0;
};


class ISliderCallback {
public:
    virtual ~ISliderCallback() {}

    virtual void RespondOnSlide(float old_value, float current_value) = 0;
};

class IWidget {
  public:
    virtual ~IWidget() {}

    virtual int32_t GetWidth() = 0;
    virtual int32_t GetHieght() = 0;
};

class IButton : public IWidget {
  public:
    virtual ~IButton() {}

    virtual void SetClickCallback(IClickCallback* callback) = 0;
};

class ISlider : public IWidget {
  public:
    virtual ~ISlider() {}

    virtual void SetSliderCallback(ISliderCallback* callback) = 0;

    virtual float GetValue() = 0;  //const
    virtual void SetValue(float value) = 0;
};

class ILabel : public IWidget {
  public:
    virtual ~ILabel() {}

    virtual void SetText(const char* text) = 0;
};

class IPreferencesPanel : public IWidget {
  public:
    virtual ~IPreferencesPanel() {}

    virtual void Attach(IWidget* widget, int32_t x, int32_t y) = 0;
};

class IWidgetFactory {
  public:
    virtual ~IWidgetFactory() {}

    virtual IButton* CreateDefaultButtonWithIcon(const char* icon_file_name) = 0;
    virtual IButton* CreateDefaultButtonWithText(const char* text) = 0;
    virtual IButton* CreateButtonWithIcon(int32_t width, int32_t height, const char* icon_file_name) = 0;
    virtual IButton* CreateButtonWithText(int32_t width, int32_t height, const char* text, int32_t char_size) = 0;

    virtual ISlider* CreateDefaultSlider(float range_min, float range_max) = 0;
    virtual ISlider* CreateSlider(int32_t width, int32_t height, float range_min, float range_max) = 0;
    virtual ISlider* CreateSlider(int32_t width, int32_t height, float thumb_width, float thumb_height, float range_min, float range_max) = 0;

    virtual ILabel*  CreateDefaultLabel(const char* text) = 0;
    virtual ILabel*  CreateLabel(int32_t width, int32_t height, const char* text, int32_t char_size) = 0;

    virtual IPreferencesPanel* CreateDefaultPreferencesPanel() = 0;
};

class IAPI {
  public:
    virtual ~IAPI() {}

    virtual IWidgetFactory*  GetWidgetFactory () = 0;
    virtual ITextureFactory* GetTextureFactory() = 0; //const
};

class IFilter {
  public:
    virtual ~IFilter() {}

    virtual void Apply(ITexture* canvas) = 0;
    virtual const char* GetName() const = 0;
    virtual IPreferencesPanel* GetPreferencesPanel() const = 0;
};

class ITool {
  public:
    virtual ~ITool() {}

    virtual void ActionBegin(ITexture* canvas, int x, int y) = 0;
    virtual void Action     (ITexture* canvas, int x, int y, int dx, int dy) = 0;
    virtual void ActionEnd  (ITexture* canvas, int x, int y) = 0;

    virtual const char* GetIconFileName() const = 0;
    virtual IPreferencesPanel* GetPreferencesPanel() const = 0;
};

class IPlugin {
  public:
    virtual ~IPlugin() {}

    virtual std::list<IFilter*> GetFilters() const = 0;
    virtual std::list<ITool*>   GetTools  () const = 0;
};
    
typedef IPlugin* (*CreateFunction) (IAPI* api);
typedef void     (*DestroyFunction)(IPlugin* plugin);
typedef uint32_t (*VersionFunction)();

} // namespace plugin

#endif /* _PLUGIN_HPP_INCLUDED_ */
