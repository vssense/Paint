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
        component_->Attach(new CanvasComponent(kDefaultPlacement));
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


PaintMainComponent::PaintMainComponent(Texture* texture) :
    GUIComponent(texture, Rectangle{0, 0, kWindowWidth, kWindowHeight})
{
    Attach(new MainTitleBar(this));
    Attach(new Border(kBorderColor, placement_));
}
