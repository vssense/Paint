#ifndef _DROP_DOWN_LIST_HPP_INCLUDED
#define _DROP_DOWN_LIST_HPP_INCLUDED

#include "gui_component.hpp"
#include "gui_system.hpp"
#include "button.hpp"

class DropDownList : public GUIComponent
{
public:
    DropDownList(const Rectangle& placement, uint32_t button_height,
                 Color button_color, Color button_hover_color);

    virtual bool OnMouseEvent(const Event& event) override;
    virtual bool ProcessListenerEvent(const Event& event) override;
    virtual bool HitTest(Vec2<int> coordinates) const override;
    virtual void Render() override;

    void AttachButton(const char* title, ICommand* command, ICommand* right_button_press = nullptr);
    void AttachButton(Texture* texture, ICommand* command, ICommand* right_button_press = nullptr);
    void AttachButton(Texture* texture, const char* name, ICommand* command, ICommand* right_button_press);

    void Hide();
    void Show();
    void ChangeVisibility();

private:
    Button* AttachButton(ICommand* command, ICommand* right_button_press = nullptr);

    int current_height_;

    int button_height_;
    Color button_color_;
    Color button_hover_color_;
    
    bool is_hidden_;
};

class DropDownListOpener : public ICommand
{
public:
    DropDownListOpener(DropDownList* list) : list_(list)
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

#endif /* _DROP_DOWN_LIST_HPP_INCLUDED */
