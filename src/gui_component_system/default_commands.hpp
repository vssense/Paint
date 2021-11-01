#ifndef _DEFAULT_COMMANDS_HPP_INCLUDED
#define _DEFAULT_COMMANDS_HPP_INCLUDED

#include "../math/swap.hpp"
#include "../commands/commands.hpp"

class DefaultHitTest : public IHitTestCommand
{
public:
    DefaultHitTest(const Rectangle& placement) : rect_(placement) {}
    virtual bool Execute(Vec2<uint32_t> position) const override
    {
        return IsInsideRectangle(rect_, position);
    }
    
    virtual void Move(Vec2<int> d) override
    {
        int new_x0 = rect_.x0 + d.x;
        int new_y0 = rect_.y0 + d.y;
        rect_.x0 = Max(new_x0, 0);
        rect_.y0 = Max(new_y0, static_cast<int>(kTitleWidth));
    }

    virtual const Rectangle& GetPlaceToRender() const override { return rect_; }
private:
    Rectangle rect_;
};

class DefaultOnEventTrue : public IOnMouseEventCommand
{
public:
    DefaultOnEventTrue() {}
    virtual bool Execute(const Event& event, Vec2<uint32_t> origin) override
    {
        return true;
    }
};

class DefaultOnEventFalse : public IOnMouseEventCommand
{
public:
    DefaultOnEventFalse() {}
    virtual bool Execute(const Event& event, Vec2<uint32_t> origin) override
    {
        return false;
    }
};

#endif /* _DEFAULT_COMMANDS_HPP_INCLUDED */
