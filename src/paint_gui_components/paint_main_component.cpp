#include "paint_main_component.hpp"
#include "canvas.hpp"

class MainTitleBar : public GUIComponent
{
public:
    MainTitleBar(PaintMainComponent* component);
};

class MainTitleClose : public ICommand
{
public:
    MainTitleClose() {}

    virtual void Execute() override
    {
        EventManager::GetInstance()->PushEvent(Event(kQuit));
    }
};

class MainTitleFile : public ICommand
{
public:
    MainTitleFile(DropDownList* list) : list_(list)
    {
        assert(list);
    }

    virtual void Execute() override
    {
        list_->ChangeVisibility();
    }

private:
    DropDownList* list_;
};

class MainTitleCanvas : public ICommand
{
public:
    MainTitleCanvas(PaintMainComponent* component) :
        component_(component) {}

    virtual void Execute() override
    {
        component_->Attach(new CanvasComponent(kDefaultCanvasPlacement));
    }

private:
    PaintMainComponent* component_;
};

class ListButtonCommand : public ICommand
{
public:
    ListButtonCommand(const char* str) : str_(str) {}

    virtual void Execute() override
    {
        printf("%s\n", str_);
    }

private:
    const char* str_;
};

MainTitleBar::MainTitleBar(PaintMainComponent* component) :
    GUIComponent(new Texture(kWindowWidth, kTitleWidth, kTitleColor),
                 Rectangle{0, 0, kWindowWidth, kTitleWidth})
{
    Attach(new Button(Rectangle{kWindowWidth - kTitleWidth, 0, kTitleWidth, kTitleWidth},
                      new MainTitleClose, new Texture("img/close.bmp"),
                      new Texture("img/close2.bmp")));

    DropDownList* list = new DropDownList(Rectangle{0, kTitleWidth, 3 * kTitleButtonsWidth / 2, kWindowHeight - kTitleWidth},
                                          kTitleWidth, kLightPurple, kWhite);

    list->AttachButton("button1", new ListButtonCommand("button1"));
    list->AttachButton("button2", new ListButtonCommand("button2"));
    list->AttachButton("button3", new ListButtonCommand("button3"));

    Button* file = new Button(Rectangle{0, 0, kTitleButtonsWidth, kTitleWidth},
                              new MainTitleFile(list), kTitleColor, kGray, kWhite, "File", kBlack);

    file->AddBorder(kBorderColor);
    file->Attach(list);
    Attach(file);
    Button* canvas = new Button(Rectangle{kTitleButtonsWidth, 0, kTitleButtonsWidth, kTitleWidth},
                                new MainTitleCanvas(component), kTitleColor, kGray, kWhite, "Canvas", kBlack);

    canvas->AddBorder(kBorderColor);
    Attach(canvas);

    Attach(new Border(kBorderColor, placement_));
    Attach(new TextIcon(placement_, "Paint", kBlack));
}

class ToolSetter : public ICommand
{
public:
    ToolSetter(ITool* tool) : tool_(tool) {}
    virtual void Execute() override
    {
        ToolManager::GetInstance()->SetActiveTool(tool_);
    }

private:
    ITool* tool_;
};

class Palette : public GUIComponent
{
public:
    Palette(const Rectangle& placement);

    virtual bool ProcessMouseEvent(const Event& event);
};

PaintMainComponent::PaintMainComponent(Texture* texture) :
    GUIComponent(texture, Rectangle{0, 0, kWindowWidth, kWindowHeight})
{

    Attach(new MainTitleBar(this));
    Attach(new Border(kBorderColor, placement_));
    Attach(new Palette(kDefaultPalettePlacement));

    Attach(new Bagel(Vec2<int>(400, 400), 200, 150, kRed));
}

bool Palette::ProcessMouseEvent(const Event& event)
{
    switch (event.GetType())
    {
        case kMouseButtonPress:
        {
            system_->Subscribe(this, kMouseHover);
            system_->Subscribe(this, kMouseMotion);
            system_->Subscribe(this, kMouseButtonRelease);
            break;
        }
        case kMouseButtonRelease:
        {
            system_->Unsubscribe(kMouseHover);
            system_->Unsubscribe(kMouseMotion);
            system_->Unsubscribe(kMouseButtonRelease);
            break;
        }
        case kMouseMotion:
        {
            Move(event.GetValue().mouse.d);
        }
        default:
        {
            break;
        }
    }

    return true;
}

Palette::Palette(const Rectangle& placement)
    : GUIComponent(new Texture(placement.w, placement.h, kWhite), placement)
{
    ITool* brush = new Brush;
    ToolManager::GetInstance()->AddTool(brush);
    Attach(new BasicButton({10, 100, 80, 30}, new ToolSetter(brush), kWhite, kBlack, "Brush"));

    void* plugin_so = dlopen("plugins/square.so", RTLD_NOW);
    assert(plugin_so);

    plugin::CreateFunction create = (plugin::CreateFunction)dlsym(plugin_so, "Create");
    assert(create);

    plugin::IPlugin* new_plugin = create(nullptr);

    ITool* loaded_tool = *new_plugin->GetTools().begin();
    Attach(new BasicButton({10, 140, 80, 30}, new ToolSetter(loaded_tool), kWhite, kBlack,
                            loaded_tool->GetIconFileName()));

    Attach(new Border(kBorderColor, Rectangle{0, 0, placement.w, placement.h}));
}
