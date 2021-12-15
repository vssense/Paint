#include <iostream>
#include <cstdlib>
#include <cstring>
#include "plugin.hpp"

struct Point {
    int x;
    int y;

    Point(int x, int y) : x(x), y(y) {};
};

namespace plugin {

class ShapesDrawer;
class Filler;

enum ShapeType {
    TYPE_SQUARE,
    TYPE_CIRCLE
};

enum ColorComponent {
    COMPONENT_RED,
    COMPONENT_GREEN,
    COMPONENT_BLUE
};

IAPI* api = nullptr;

void MakeSliderWithTitle(int size_x, int size_y, int coord_x, int coord_y, int max_val, int min_val, char* title, 
                         IPreferencesPanel* panel, ISliderCallback* callback,
                         int title_size_x = 80, int title_size_y = 30, int ch_size = 10);

void MakeSliderWithTitleMeasure(int size_x, int size_y, int coord_x, int coord_y, int max_val, int min_val, char* title, 
                         IPreferencesPanel* panel, ILabel* num_label, ISliderCallback* callback,
                         int title_size_x = 80, int title_size_y = 30, int ch_size = 10);


class ChangeShapeeCallback : public IClickCallback {
  public:
    ChangeShapeeCallback(ShapesDrawer* drawer, ShapeType type);
    virtual ~ChangeShapeeCallback() {};

    virtual void RespondOnClick() override;

  private:
    ShapesDrawer* drawer;
    ShapeType type;
};

class ChangeColorSlideCallback : public ISliderCallback {
  public:
    ChangeColorSlideCallback(ShapesDrawer* drawer, ILabel* num_label, ColorComponent component);
    virtual ~ChangeColorSlideCallback() {};

    virtual void RespondOnSlide(float old_value, float current_value) override;

  private:
    ShapesDrawer* drawer;
    ILabel* num_label;
    ColorComponent component;
};

class ChangeSizeSlideCallback : public ISliderCallback {
  public:
    ChangeSizeSlideCallback(ShapesDrawer* drawer, ILabel* num_label);
    virtual ~ChangeSizeSlideCallback() {};

    virtual void RespondOnSlide(float old_value, float current_value) override;

  private:
    ShapesDrawer* drawer;
    ILabel* num_label;
};

class TestCallback : public IClickCallback {
  public:
    TestCallback();
    virtual ~TestCallback() {}

    virtual void RespondOnClick() override;
  private:
};

class TestSliderCallback : public ISliderCallback {
  public:
    TestSliderCallback();
    virtual ~TestSliderCallback() {};

    virtual void RespondOnSlide(float old_value, float current_value) override;
};

class Filler : public IFilter {
  public:
    Filler();
    virtual ~Filler() {};

    virtual void Apply(ITexture* canvas) override;
    virtual const char* GetName() const override;

    virtual IPreferencesPanel* GetPreferencesPanel() const override;

    void ConstructPreferencePanel();

  private:
    IPreferencesPanel* panel;
};

class ShapesDrawer : public ITool {
  public:
    ShapesDrawer();
    virtual ~ShapesDrawer() {};

    virtual void ActionBegin(ITexture* canvas, int x, int y) override;

    void SetSize(int new_size);
    Color GetColor() const { return color; };
    void SetColor(Color new_color) { color = new_color; };
    void SetShape(ShapeType new_type) { type = new_type; };


    virtual void Action     (ITexture* canvas, int x, int y, int dx, int dy) override {};
    virtual void ActionEnd  (ITexture* canvas, int x, int y) override {};

    virtual const char* GetName() const override;
    virtual const char* GetIconFileName() const override;

    virtual IPreferencesPanel* GetPreferencesPanel() const override;

    void ConstructPreferencePanel();

  private:
    IPreferencesPanel* panel;
    ShapeType type;
    int size;
    Color color;
};

class Plugin : public IPlugin {
  public:
    Plugin(Filler* filler, ShapesDrawer* drawer);
    ~Plugin() {};

    virtual std::list<IFilter*> GetFilters() const override;

    virtual std::list<ITool*> GetTools () const override;

  private:
    Filler* filler;
    ShapesDrawer* drawer;
};

}

extern "C" plugin::IPlugin* Create(plugin::IAPI* gui_api) {
    plugin::api = gui_api;
    return new plugin::Plugin(new plugin::Filler(), new plugin::ShapesDrawer());
};

extern "C" void Destroy(plugin::IPlugin* plugin) {
    delete plugin;
};

extern "C" uint32_t Version() {
    return plugin::kVersion;
};

namespace plugin {

void MakeSliderWithTitle(int size_x, int size_y, int coord_x, int coord_y, int max_val, int min_val, char* title, 
                         IPreferencesPanel* panel, ISliderCallback* callback,
                         int title_size_x, int title_size_y, int ch_size) {

    ILabel* label = api->GetWidgetFactory()->CreateLabel(title_size_x, title_size_y, title, ch_size);
    panel->Attach(label, coord_x + size_x / 2 - title_size_x / 2, coord_y - title_size_y);
    
    ISlider* slider_size = api->GetWidgetFactory()->CreateSlider(size_x, size_y, max_val, min_val);
    slider_size->SetSliderCallback(callback);
    panel->Attach(slider_size, coord_x, coord_y);
};

void MakeSliderWithTitleMeasure(int size_x, int size_y, int coord_x, int coord_y, int max_val, int min_val, char* title, 
                         IPreferencesPanel* panel, ILabel* num_label, ISliderCallback* callback,
                         int title_size_x, int title_size_y, int ch_size) {
                             
    ILabel* label = api->GetWidgetFactory()->CreateLabel(title_size_x, title_size_y, title, ch_size);
    panel->Attach(label, coord_x + size_x / 2 - title_size_x / 2, coord_y - title_size_y);
    panel->Attach(num_label, coord_x + size_x / 2 + title_size_x / 8, coord_y - title_size_y);

    ISlider* slider_size = api->GetWidgetFactory()->CreateSlider(size_x, size_y, max_val, min_val);
    slider_size->SetSliderCallback(callback);
    panel->Attach(slider_size, coord_x, coord_y);
};

ChangeShapeeCallback::ChangeShapeeCallback(ShapesDrawer* drawer, ShapeType type) : drawer(drawer), type(type) {};
void ChangeShapeeCallback::RespondOnClick() {
    drawer->SetShape(type);
};

ChangeColorSlideCallback::ChangeColorSlideCallback(ShapesDrawer* drawer, ILabel* num_label, ColorComponent component) : drawer(drawer), num_label(num_label), component(component) {};
void ChangeColorSlideCallback::RespondOnSlide(float old_value, float current_value) {
    Color color = drawer->GetColor();

    static char buf[4] = {};

    switch(component) {
        case COMPONENT_RED:
            color &= 0xFF'FF'FF'00;
            color |= static_cast<uint32_t>(current_value) << 0;
        break;

        case COMPONENT_GREEN:
            color &= 0xFF'FF'00'FF;
            color |= static_cast<uint32_t>(current_value) << 8;
        break;

        case COMPONENT_BLUE:
            color &= 0xFF'00'FF'FF;
            color |= static_cast<uint32_t>(current_value) << 16;
        break;

        default:
        break;
    }

    memset(buf, 0, 4);
    sprintf(buf, "%d", static_cast<int32_t>(current_value));

    // itoa(static_cast<uint32_t>(current_value), buf, 10);
    num_label->SetText(buf);

    drawer->SetColor(color);
};

ChangeSizeSlideCallback::ChangeSizeSlideCallback(ShapesDrawer* drawer, ILabel* num_label) : drawer(drawer), num_label(num_label) {};
void ChangeSizeSlideCallback::RespondOnSlide(float old_value, float current_value) {
    drawer->SetSize(static_cast<int>(current_value));
    static char buf[4] = {};
    memset(buf, 0, 4);
    sprintf(buf, "%d", static_cast<int32_t>(current_value));
    // itoa(static_cast<uint32_t>(current_value), buf, 10);
    num_label->SetText(buf);
};

TestCallback::TestCallback() {};
void TestCallback::RespondOnClick() { 
    std::cout << "click callback!\n";
};

TestSliderCallback::TestSliderCallback() {};
void TestSliderCallback::RespondOnSlide(float old_value, float current_value) {
    std::cout << "new value: " << current_value <<"\n";
};

Filler::Filler() {
    this->ConstructPreferencePanel();
};

void Filler::Apply(ITexture* canvas) {
    canvas->DrawRect(0, 0, canvas->GetWidth(), canvas->GetHieght(), 0x00'FF'00'FF);    
};

const char* Filler::GetName() const {
    static const char* name = "Filler";
    return name;
};

IPreferencesPanel* Filler::GetPreferencesPanel() const {
    return nullptr;
};

void Filler::ConstructPreferencePanel() {
    panel = api->GetWidgetFactory()->CreateDefaultPreferencesPanel();

    IButton* text_button = api->GetWidgetFactory()->CreateButtonWithText(120, 30, "Press me", 10);
    text_button->SetClickCallback(new TestCallback());

    panel->Attach(text_button, panel->GetWidth() / 2, panel->GetHieght() / 2);
};

ShapesDrawer::ShapesDrawer() : type(TYPE_CIRCLE), size(1), color(0xFF'00'00'00) {
    this->ConstructPreferencePanel();
};
void ShapesDrawer::ActionBegin(ITexture* canvas, int x, int y) {
    std::cout << "started drawing shapes!\n";
    switch (type) {
        case TYPE_CIRCLE:
            canvas->DrawCircle(x, y, size, color);
        break;
    
        case TYPE_SQUARE:
            canvas->DrawRect(x - size / 2, y - size / 2, x + size / 2, y + size / 2, color);
        break;

        default:
            std::cout << "unkonw type: " << type << "\n";
        break;
    }    
};

void ShapesDrawer::SetSize(int new_size) { 
    size = new_size;
};

const char* ShapesDrawer::GetName() const
{
    return "Vitya";
}

const char* ShapesDrawer::GetIconFileName() const {
    static const char* name = "img/vitya.bmp";
    return name;
};

IPreferencesPanel* ShapesDrawer::GetPreferencesPanel() const {
    return panel;
};
void ShapesDrawer::ConstructPreferencePanel() {
    IWidgetFactory* factory = api->GetWidgetFactory();
    
    panel = api->GetWidgetFactory()->CreateDefaultPreferencesPanel();

    ILabel* tool_name = api->GetWidgetFactory()->CreateLabel(170, 30 , "Shapes drawer", 12);
    panel->Attach(tool_name, panel->GetWidth() / 2 - 170 / 2, 5);

    Point coord();
    int button_x = 5 * panel->GetWidth() / 8;
    int button_y = panel->GetHieght() / 8;
    int dy = 10;
    int button_size_x = 80;
    int button_size_y = 30;
    
    IButton* circle_button = api->GetWidgetFactory()->CreateButtonWithText(button_size_x, button_size_y, "Circle", 10);
    circle_button->SetClickCallback(new ChangeShapeeCallback(this, TYPE_CIRCLE));
    panel->Attach(circle_button, button_x, button_y);

    IButton* square_button = api->GetWidgetFactory()->CreateButtonWithText(button_size_x, button_size_y, "Square", 10);
    square_button->SetClickCallback(new ChangeShapeeCallback(this, TYPE_SQUARE));
    panel->Attach(square_button, button_x, button_y + button_size_y + dy);
    
    //ILabel* asdfa = factory->CreateLabel(50, 30, "0", 10);

    ILabel* red_count   = factory->CreateLabel(50, 30, "0", 10);
    ILabel* green_count = factory->CreateLabel(50, 30, "0", 10);
    ILabel* blue_count  = factory->CreateLabel(50, 30, "0", 10);
    ILabel* size_count  = factory->CreateLabel(50, 30, "1", 10);

    MakeSliderWithTitleMeasure(150, 15, panel->GetWidth() / 8, panel->GetHieght() / 5 + 0  , 1, 100, "size:",  panel, size_count,  new ChangeSizeSlideCallback(this, size_count));
    MakeSliderWithTitleMeasure(150, 15, panel->GetWidth() / 8, panel->GetHieght() / 5 + 60 , 0, 255, "red:",   panel, red_count,   new ChangeColorSlideCallback(this, red_count,   COMPONENT_RED));
    MakeSliderWithTitleMeasure(150, 15, panel->GetWidth() / 8, panel->GetHieght() / 5 + 120, 0, 255, "green:", panel, green_count, new ChangeColorSlideCallback(this, green_count, COMPONENT_GREEN));
    MakeSliderWithTitleMeasure(150, 15, panel->GetWidth() / 8, panel->GetHieght() / 5 + 180, 0, 255, "blue:",  panel, blue_count,  new ChangeColorSlideCallback(this, blue_count,  COMPONENT_BLUE));


    //ILabel* name_size = api->GetWidgetFactory()->CreateLabel(80, 30, "size", 11);
    //panel->Attach(tool_name, panel->GetWidth() / 8 + 150 / 2 - 40, panel->GetHieght() / 4 - 30);
    //ISlider* slider_size = api->GetWidgetFactory()->CreateSlider(150, 25, 0, 255);
    //slider_size->SetSliderCallback(new TestSliderCallback());
    //panel->Attach(slider_size, panel->GetWidth() / 8, panel->GetHieght() / 4);
};

Plugin::Plugin(Filler* filler, ShapesDrawer* drawer) : filler(filler), drawer(drawer) {}

std::list<IFilter*> Plugin::GetFilters() const {
    std::list<IFilter*> filter_list;
    filter_list.push_back(filler);
    return filter_list;
};

std::list<ITool*> Plugin::GetTools () const {
    std::list<ITool*> tool_list;
    tool_list.push_back(drawer);
    return tool_list;
};

}