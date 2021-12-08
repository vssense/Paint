#include "paint_main_component.hpp"
#include "canvas.hpp"
#include "../instruments/plugin_manager.hpp"
#include "../gui_system/slider.hpp"
#include "../api/api_widgets.hpp"

class MainTitleBar : public GUIComponent
{
public:
    MainTitleBar(PaintMainComponent* component);
    Button* CreateTools(const Rectangle& placement);
    void AttachPluginsTools(DropDownList* tools);
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

class ToolSetter : public ICommand
{
public:
    ToolSetter(ITool* tool) : tool_(tool) {}
    virtual void Execute() override
    {
        Manager<ITool>::GetInstance()->SetActive(tool_);
    }

private:
    ITool* tool_;
};

class PreferencesPanelOpener : public ICommand
{
public:
    PreferencesPanelOpener(ITool* tool, MainTitleBar* title_bar)
        : tool_(tool), title_bar_(title_bar) {}

    virtual void Execute() override
    {
        APIPreferencesPanel* panel = dynamic_cast<APIPreferencesPanel*>(tool_->GetPreferencesPanel());

        Manager<ITool>::GetInstance()->SetActive(tool_);

        if (panel != nullptr)
        {
            title_bar_->Detach(panel->GetBasicWidget());
            title_bar_->Attach(panel->GetBasicWidget());
        }
    }

private:
    ITool* tool_;
    MainTitleBar* title_bar_;
};

Button* MainTitleBar::CreateTools(const Rectangle& placement)
{
    DropDownList* tools = new DropDownList(Rectangle{0, placement.h, 3 * placement.w / 2, kWindowHeight / 2},
                                                     kTitleWidth, kLightPurple, kWhite);

    Brush* brush = new Brush;
    tools->AttachButton("Brush", new ToolSetter(brush), new PreferencesPanelOpener(brush, this));

    Manager<ITool>::GetInstance()->Add(brush);
    Button* tool = new Button(placement, new DropDownListOpener(tools), kTitleColor,
                              kGray, kWhite, "Tool", kBlack);

    AttachPluginsTools(tools);

    tool->Attach(tools);
    tool->AddBorder(kBorderColor);

    return tool;
}

void MainTitleBar::AttachPluginsTools(DropDownList* tools)
{
    assert(tools);

    PluginManager* manager = PluginManager::GetInstance();
    for (Plugin* loaded : manager->GetPlugins())
    {
        IPlugin* plugin = loaded->GetPlugin();

        if (plugin == nullptr)
        {
            continue;
        }

        for (ITool* tool : plugin->GetTools())
        {
            tools->AttachButton(tool->GetIconFileName(), new ToolSetter(tool),
                                new PreferencesPanelOpener(tool, this));
        }
    }
}

MainTitleBar::MainTitleBar(PaintMainComponent* component) :
    GUIComponent(new Texture(kWindowWidth, kTitleWidth, kTitleColor),
                 Rectangle{0, 0, kWindowWidth, kTitleWidth})
{
    Attach(new Button(Rectangle{kWindowWidth - kTitleWidth, 0, kTitleWidth, kTitleWidth},
                      new MainTitleClose, new Texture("img/close.bmp"),
                      nullptr, new Texture("img/close2.bmp")));

    DropDownList* list = new DropDownList(Rectangle{0, kTitleWidth, 3 * kTitleButtonsWidth / 2, kWindowHeight - kTitleWidth},
                                          kTitleWidth, kLightPurple, kWhite);

    list->AttachButton("button1", new ListButtonCommand("button1"));
    list->AttachButton("button2", new ListButtonCommand("button2"));
    list->AttachButton("button3", new ListButtonCommand("button3"));

    Button* file = new Button(Rectangle{0, 0, kTitleButtonsWidth, kTitleWidth},
                              new DropDownListOpener(list), kTitleColor, kGray, kWhite, "File", kBlack);

    file->AddBorder(kBorderColor);
    file->Attach(list);
    Attach(file);
    Button* canvas = new Button(Rectangle{kTitleButtonsWidth, 0, kTitleButtonsWidth, kTitleWidth},
                                new MainTitleCanvas(component), kTitleColor, kGray, kWhite, "Canvas", kBlack);

    canvas->AddBorder(kBorderColor);

    Attach(canvas);
    Attach(CreateTools(Rectangle{2 * kTitleButtonsWidth, 0, kTitleButtonsWidth, kTitleWidth}));
    AddBorder(kBorderColor);
    Attach(new TextIcon(placement_, "Paint", kBlack));
}

PaintMainComponent::PaintMainComponent(Texture* texture) :
    GUIComponent(texture, Rectangle{0, 0, kWindowWidth, kWindowHeight})
{

    Attach(new MainTitleBar(this));

    AddBorder(kBorderColor);

    Attach(new Bagel(Vec2<int>(400, 400), 200, 150, kRed));
}
