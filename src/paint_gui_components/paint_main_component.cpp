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
    MainTitleFile() {}

    virtual void Execute() override
    {
        printf("File button pressed\n");
    }
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

MainTitleBar::MainTitleBar(PaintMainComponent* component) :
    GUIComponent(new Texture(kWindowWidth, kTitleWidth, kTitleColor),
                 Rectangle{0, 0, kWindowWidth, kTitleWidth})
{
    Attach(new Button(Rectangle{kWindowWidth - kTitleWidth, 0, kTitleWidth, kTitleWidth},
                      new MainTitleClose, new Texture("img/close.bmp"),
                      new Texture("img/close2.bmp")));

    Button* file = new Button(Rectangle{0, 0, kTitleButtonsWidth, kTitleWidth},
                              new MainTitleFile, kTitleColor, kGray, kWhite, "File", kBlack);

    file->AddBorder(kBorderColor);
    Attach(file);
    Button* canvas = new Button(Rectangle{kTitleButtonsWidth, 0, kTitleButtonsWidth, kTitleWidth},
                                new MainTitleCanvas(component), kTitleColor, kGray, kWhite, "Canvas", kBlack);

    canvas->AddBorder(kBorderColor);
    Attach(canvas);

    Attach(new Border(kBorderColor, placement_));
    Attach(new TextIcon(placement_, "Paint", kBlack));
}

class ActiveToolColorSetter : public ICommand
{
public:
    ActiveToolColorSetter(Color color) : color_(color) {}
    virtual void Execute() override
    {
        ToolManager::GetInstance()->GetActiveTool()->SetColor(color_);
    }

private:
    Color color_;
};

class ToolSetter : public ICommand
{
public:
    ToolSetter(Tool* tool) : tool_(tool) {}
    virtual void Execute() override
    {
        ToolManager::GetInstance()->SetActiveTool(tool_);
    }

private:
    Tool* tool_;
};

class Palette : public GUIComponent
{
public:
    Palette(const Rectangle& placement) :
        GUIComponent(new Texture(placement.w, placement.h, kWhite), placement)
    {
        Attach(new BasicButton({10, 10, 20, 20}, new ActiveToolColorSetter(kWhite) , kWhite));
        Attach(new BasicButton({40, 10, 20, 20}, new ActiveToolColorSetter(kBlack) , kBlack));
        Attach(new BasicButton({70, 10, 20, 20}, new ActiveToolColorSetter(kRed)   , kRed));
        Attach(new BasicButton({10, 40, 20, 20}, new ActiveToolColorSetter(kYellow), kYellow));
        Attach(new BasicButton({40, 40, 20, 20}, new ActiveToolColorSetter(kBlue)  , kBlue));
        Attach(new BasicButton({70, 40, 20, 20}, new ActiveToolColorSetter(kGreen) , kGreen));

        Tool* brush = new Brush;
        ToolManager::GetInstance()->AddTool(brush);
        Attach(new BasicButton({10, 100, 80, 30}, new ToolSetter(brush), kWhite, kBlack, "Brush"));

        void* plugin = dlopen("src/plugins/square.so", RTLD_NOW);

        Tool* loaded_tool = GetToolPtr(dlsym(plugin, "GetTool"))();
        Attach(new BasicButton({10, 140, 80, 30}, new ToolSetter(loaded_tool), kWhite, kBlack,
                               GetNamePtr(dlsym(plugin, "GetName"))()));

        Attach(new Border(kBorderColor, Rectangle{0, 0, placement.w, placement.h}));
    }

    virtual bool ProcessMouseEvent(const Event& event);
};

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

PaintMainComponent::PaintMainComponent(Texture* texture) :
    GUIComponent(texture, Rectangle{0, 0, kWindowWidth, kWindowHeight})
{

    Attach(new MainTitleBar(this));
    Attach(new Border(kBorderColor, placement_));
    Attach(new Palette(kDefaultPalettePlacement));

    Attach(new Bagel(Vec2<int>(400, 400), 200, 150, kRed));
}
