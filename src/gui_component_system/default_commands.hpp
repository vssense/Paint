#ifndef _DEFAULT_COMMANDS_HPP_INCLUDED
#define _DEFAULT_COMMANDS_HPP_INCLUDED

class DefaultHitTest : public IHitTestCommand
{
public:
    DefaultHitTest(const Rectangle& placement) : rect_(placement) {}
    virtual bool Execute(Vec2<uint32_t> position) const override
    {
        return IsInsideRectangle(rect_, position);
    }

    virtual const Rectangle& GetPlaceToRender() const override { return rect_; }
private:
    Rectangle rect_;
};

class DefaultOnEvent : public IOnMouseEventCommand
{
public:
    DefaultOnEvent() {}
    virtual bool Execute(const Event& event) override
    {
        return true;
    }
};

#endif /* _DEFAULT_COMMANDS_HPP_INCLUDED */
