#include "brush.hpp"

class SetColor : public ICommand
{
public:
    SetColor(Color color, Color* place_to_assign)
        : color_(color), place_to_assign_(place_to_assign) {}

    virtual void Execute() override
    {
        *place_to_assign_ = color_;
    }

private:
    Color color_;
    Color* place_to_assign_;
};

Brush::Brush() : color_(kBlack), panel_(nullptr)
{
    PreferencesPanel* panel = new PreferencesPanel;

    panel->Attach(new Button(Rectangle{20, 20, 30, 30}, new SetColor(kRed, &color_),
                  new Texture(30, 30, kRed, kBlack)));

    panel->Attach(new Button(Rectangle{60, 20, 30, 30}, new SetColor(kBlue, &color_),
                  new Texture(30, 30, kBlue, kBlack)));

    panel_ = new APIPreferencesPanel(panel);
}

Brush::~Brush()
{
    delete panel_;
}

void Brush::ActionBegin(ITexture* canvas, int x, int y)
{
    assert(canvas);
    
    canvas->DrawCircle(x, y, 10, color_);
}

void Brush::Action(ITexture* canvas, int x, int y, int dx, int dy)
{
    assert(canvas);

    canvas->DrawThickLine(x, y, x + dx, y + dy, 10, color_);
}

void Brush::ActionEnd(ITexture* canvas, int x, int y)
{
    assert(canvas);

    canvas->DrawCircle(x, y, 10, color_);
}

const char* Brush::GetName() const
{
    return "Brush";
}

const char* Brush::GetIconFileName() const
{
    return "img/brush.bmp";
}

IPreferencesPanel* Brush::GetPreferencesPanel() const
{
    return panel_;
}
